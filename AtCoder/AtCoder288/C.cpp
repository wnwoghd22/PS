#include <iostream>
#include <vector>

const int LEN = 200'001;
bool visited[LEN];
std::vector<int> graph[LEN];
int N, M, A, B;

int dfs(int u, int o) {
	visited[u] = true;
	int result = 0;
	for (const int& v : graph[u]) {
		if (v == o) continue;
		if (visited[v]) ++result;
		else result += dfs(v, u);
	}
	return result;
}

int main() {
	std::cin >> N >> M;
	while (M--) {
		std::cin >> A >> B;
		graph[A].push_back(B);
		graph[B].push_back(A);
	}
	int result = 0;
	for (int u = 1; u <= N; ++u) {
		if (!visited[u])
			result += dfs(u, -1);
	}
	std::cout << result / 2;
}