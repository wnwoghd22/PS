#include <iostream>
#include <cstring>
#include <vector>

int N, M, U, V;

std::vector<int> g[101];
int visited[101];

void dfs(int u, int p = 0) {
	visited[u] = visited[p] + 1;
	for (const int& v : g[u]) {
		if (v == p) continue;
		dfs(v, u);
	}
}

int main() {
	std::cin >> N;
	std::cin >> U >> V;
	std::cin >> M;
	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	memset(visited, -1, sizeof visited);
	dfs(U);
	std::cout << visited[V];
}