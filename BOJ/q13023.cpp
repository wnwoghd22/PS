#include <iostream>
#include <vector>

const int LEN = 2000;
int N, M, visited[LEN];

std::vector<int> g[LEN];
bool dfs(int u) {
	if (visited[u] == 5) return true;
	for (const int& v : g[u]) {
		if (!visited[v]) {
			visited[v] = visited[u] + 1;
			if (dfs(v)) return true;
		}
	}
	return visited[u] = 0;
}

int main() {
	std::cin >> N >> M;
	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	M = 0;
	for (int i = 0; i < N; ++i) {
		if (M |= dfs(i)) break;
	}
	std::cout << M;
}