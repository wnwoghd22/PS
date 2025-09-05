#include <iostream>
#include <cstring>

const int LEN = 200'001;

struct Query {
	int x, u, v;
} q[LEN * 2];

int N, Q, P[LEN], p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

int main() {
	memset(p, -1, sizeof p);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> Q;
	for (int u = 2, v; u <= N; ++u) {
		std::cin >> v;
		P[u] = v;
	}
	for (int i = 0; i < N - 1 + Q; ++i) {
		std::cin >> q[i].x;
		if (q[i].x == 0) std::cin >> q[i].u;
		if (q[i].x == 1) std::cin >> q[i].u >> q[i].v;
	}
	for (int i = N + Q - 2; i >= 0; --i) {
		if (q[i].x == 0) join(q[i].u, P[q[i].u]);
		if (q[i].x == 1 && find(q[i].u) == find(q[i].v)) q[i].x = -1;
	}
	for (int i = 0; i < N - 1 + Q; ++i)
		if (q[i].x) std::cout << (q[i].x > 0 ? "NO\n" : "YES\n");
}