#include <iostream>
#include <cstring>

typedef long long ll;
const int LEN = 2e5 + 1;

int N, M, p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}
int degree[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	memset(p, -1, sizeof p);
	std::cin >> N >> M;
	for (int i = 0, a, b; i < M; ++i) {
		std::cin >> a >> b;
		degree[a]++, degree[b]++;
		join(a, b);
	}
	for (int u = 1, v; u <= N; ++u) {
		v = find(u);
		if (v != u) degree[v] += degree[u];
	}
	ll ret = 0;
	for (int i = 1; i <= N; ++i) {
		if (i != find(i)) continue;
		ll sz = -p[i];
		if (sz > 2) {
			ret += sz * (sz - 1) / 2 - degree[i] / 2;
		}
	}
	std::cout << ret;
}