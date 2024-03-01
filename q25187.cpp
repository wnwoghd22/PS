#include <iostream>
#include <cstring>

const int LEN = 100'001;

int N, M, Q, C[LEN], p[LEN];

int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], C[a] += C[b], p[b] = a;
	else p[b] += p[a], C[b] += C[a], p[a] = b;
	return 1;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M >> Q;
	memset(p, -1, sizeof p);
	for (int i = 1; i <= N; ++i) std::cin >> C[i];
	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		join(u, v);
	}
	for (int i = 0, u; i < Q; ++i) {
		std::cin >> u;
		u = find(u);
		std::cout << (C[u] * 2 > -p[u]) << '\n';
	}
}