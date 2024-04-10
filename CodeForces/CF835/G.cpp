#include <iostream>
#include <queue>
#include <set>
#include <cstring>

const int LEN = 1e5 + 1;

bool visited[LEN];
std::vector<std::pair<int,int>> graph[LEN];
std::set<int> S;

int N, A, B;

void dfs(int u, int bit) {
	visited[u] = true;
	S.insert(bit);
	for (const auto& [v, w] : graph[u]) {
		if (!visited[v]) {
			if (v == B && (bit ^ w)) continue;
			dfs(v, bit ^ w);
		}
	}
}

int bfs(int i) {
	std::queue<std::pair<int, int>> q;
	memset(visited, 0, sizeof visited);
	q.push({ i, 0 });
	visited[i] = true;
	while (!q.empty()) {
		auto [u, bit] = q.front(); q.pop();

		if (S.find(bit) != S.end() && u != i) return 1;

		for (const auto& [v, w] : graph[u]) {
			if (!visited[v]) {
				visited[v] = true;
				q.push({ v, bit ^ w });
			}
		}
	}
	return 0;
}

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		memset(visited, 0, sizeof visited);
		for (auto& v : graph) v.clear();
		S.clear();
		
		std::cin >> N >> A >> B;

		for (int u, v, w, i = 1; i < N; ++i) {
			std::cin >> u >> v >> w;
			graph[u].push_back({ v, w });
			graph[v].push_back({ u, w });
		}

		dfs(A, 0);
		if (visited[B]) std::cout << "YES\n";
		else if (bfs(B)) std::cout << "YES\n";
		else std::cout << "NO\n";
	}
}