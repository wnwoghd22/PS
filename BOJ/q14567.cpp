#include <iostream>
#include <vector>
#include <queue>

const int LEN = 1001;

std::vector<int> graph[LEN];

int N, M;
int incoming[LEN];
int dp[LEN];

void topo_sort() {
	std::queue<int> q;

	for (int i = 1; i <= N; ++i) {
		if (!incoming[i]) {
			dp[i] = 1;
			q.push(i);
		}
	}

	while (q.size()) {
		int u = q.front(); q.pop();
		for (const int& v : graph[u]) {
			dp[v] = dp[u] + 1;
			if (!--incoming[v])
				q.push(v);
		}
	}
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;

	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		++incoming[v];
	}
	topo_sort();

	for (int i = 1; i <= N; ++i) std::cout << dp[i] << ' ';
}