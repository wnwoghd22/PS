#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 10'000;
std::vector<int> graph[LEN];
int V, E, A, B, visited[LEN];
bool is_cut[LEN];

int dfs(int u, int order = 1, bool root = true) {
	int min = visited[u] = order, child = 0;
	for (const int& v : graph[u]) {
		if (visited[v]) min = std::min(min, visited[v]);
		else {
			++child;
			int next = dfs(v, order + 1, false);
			if (!root && next >= order) is_cut[u] = true; // if all visited order of next nodes are bigger
			min = std::min(min, next);
		}
	}
	if (root) is_cut[u] = child >= 2;
	return min;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> V >> E;
	while (E--) {
		std::cin >> A >> B;
		graph[A].push_back(B);
		graph[B].push_back(A);
	}
	for (int u = 1; u <= V; ++u)
		if (!visited[u])
			dfs(u);
	int count = 0;
	std::vector<int> result;
	for (int u = 1; u <= V; ++u) {
		if (is_cut[u]) {
			++count;
			result.push_back(u);
		}
	}
	std::cout << count << '\n';
	for (const int& v : result) std::cout << v << ' ';
}