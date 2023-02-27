#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 100'001;
const int LOG_L = 18;

int table[LEN][LOG_L];
int dist[LEN][LOG_L];

int N, W[LEN];
struct Edge { int v, w; };
std::vector<Edge> graph[LEN];

void dfs(int u, int p = 0, int w = 0) {
	table[u][1] = p;
	dist[u][1] = w;
	for (int i = 2, v = p; v; v = table[v][i - 1], ++i) {
		table[u][i] = table[v][i - 1];
		dist[u][i] = dist[u][i - 1] + dist[v][i - 1];
	}

	for (const Edge& e : graph[u]) {
		if (e.v == p) continue;
		dfs(e.v, u, e.w);
	}
}

int query(int u, int w) {
	if (u == 1) return 1;
	int i = 0;
	while (table[u][i + 1] && dist[u][i + 1] <= w) ++i;
	if (i == 0) return u;
	return query(table[u][i], w - dist[u][i]);
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> W[i];
	for (int i = 1, u, v, w; i < N; ++i) {
		std::cin >> u >> v >> w;
		graph[u].push_back({ v, w });
		graph[v].push_back({ u, w });
	}
	dfs(1);
	for (int i = 1; i <= N; ++i) std::cout << query(i, W[i]) << '\n';
}