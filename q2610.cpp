#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 101;
const int INF = 300;

int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (a > b) std::swap(a, b);
	p[a] += p[b]; p[b] = a;
	return 1;
}

int N, M, K, d[LEN][LEN], w[LEN], x[LEN], y[LEN];

int main() {
	std::cin >> N >> M;
	memset(p, -1, sizeof p);
	for (int u = 1; u <= N; ++u)
		for (int v = 1; v <= N; ++v)
			d[u][v] = INF * (u != v);

	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		join(u, v);
		d[u][v] = d[v][u] = 1;
	}

	for (int k = 1; k <= N; ++k)
		for (int u = 1; u <= N; ++u)
			for (int v = 1; v <= N; ++v)
				d[u][v] = std::min(d[u][v], d[u][k] + d[k][v]);

	for (int u = 1; u <= N; ++u)
		for (int v = 1; v <= N; ++v)
			if (u != v && d[u][v] < INF) w[u] = std::max(w[u], d[u][v]);

	for (int u = 1; u <= N; ++u) find(u), x[u] = u;
	for (int u = 1, v; u <= N; ++u) {
		v = find(u);
		if (u == v) ++K;
		if (w[u] < w[x[v]]) x[v] = u;
	}


	for (int u = 1, j = 0; u <= N; ++u)
		if (u == find(u)) y[j++] = x[u];
	std::sort(y, y + K);

	std::cout << K << '\n';
	for (int i = 0; i < K; ++i) std::cout << y[i] << '\n';
}