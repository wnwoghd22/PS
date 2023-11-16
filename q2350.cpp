#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

const int LEN = 1001;

struct Edge {
	int u, v, w;
	bool operator<(const Edge& r) const { return w > r.w; }
} e[100'000];

int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

std::vector<int> g[LEN];
int w[LEN][LEN], d[LEN][LEN];
void dfs(int u, int s, int x) {
	d[s][u] = x;
	for (const int& v : g[u]) {
		if (!d[s][v]) 
			dfs(v, s, w[u][v] < x ? w[u][v] : x);
	}
}

int N, M, K;

int main() {
	std::cin >> N >> M >> K;
	for (int i = 0; i < M; ++i) std::cin >> e[i].u >> e[i].v >> e[i].w;
	memset(p, -1, sizeof p);
	std::sort(e, e + M);
	for (int i = 0; i < M; ++i) {
		if (join(e[i].u, e[i].v)) {
			g[e[i].u].push_back(e[i].v);
			g[e[i].v].push_back(e[i].u);
			w[e[i].u][e[i].v] = w[e[i].v][e[i].u] = e[i].w;
		}
	}
	for (int i = 1; i <= N; ++i) dfs(i, i, 200);
	for (int i = 0, u, v; i < K; ++i) {
		std::cin >> u >> v;
		std::cout << d[u][v] << '\n';
	}
}