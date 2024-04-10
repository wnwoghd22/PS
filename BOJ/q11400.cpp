#include <iostream>
#include <vector>
#include <algorithm>

const int LEN = 100'001;
std::vector<int> graph[LEN];
int V, E, A, B, visited[LEN];
std::vector<std::pair<int, int>> cut;

int dfs(int u, int p = 0) {
	int min = visited[u] = visited[p] + 1;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		if (visited[v]) min = std::min(min, visited[v]);
		else {
			int next = dfs(v, u);
			if (next > visited[u]) {
				if (u < v) cut.push_back({ u, v });
				else cut.push_back({ v, u });
			}
			min = std::min(min, next);
		}
	}
	return min;
}

int main() {
	std::cin >> V >> E;
	while (E--) {
		std::cin >> A >> B;
		graph[A].push_back(B);
		graph[B].push_back(A);
	}
	for (int u = 1; u <= V; ++u)
		if (!visited[u])
			dfs(u);
	std::sort(cut.begin(), cut.end());
	std::cout << cut.size() << '\n';
	for (const std::pair<int, int>& e : cut)
		std::cout << e.first << ' ' << e.second << '\n';
}