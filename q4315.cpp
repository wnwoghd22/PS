#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>

typedef long long int ll;
const int LEN = 10'001;
std::vector<int> graph[LEN];
ll dp[LEN], count[LEN], tree_size[LEN];
int N, u, c, d, v, visited[LEN];

void dfs(int u) {
	visited[u] = true;
	tree_size[u] = 1;
	for (const int& v : graph[u]) {
		if (visited[v]) continue;
		dfs(v);
		tree_size[u] += tree_size[v];
		count[u] += count[v];
		dp[u] += dp[v];
	}
	dp[u] += std::abs(count[u] - tree_size[u]);
}

int main() {
	freopen("input.txt", "r", stdin);
	while (1) {
		std::cin >> N;
		if (!N) break;
		for (std::vector<int>& v : graph) v.clear();
		memset(dp, 0, sizeof dp);
		memset(count, 0, sizeof count);
		memset(tree_size, 0, sizeof tree_size);
		memset(visited, 0, sizeof visited);

		for (int i = 0; i < N; ++i) {
			std::cin >> u >> c >> d;
			count[u] = c;
			while (d--) {
				std::cin >> v;
				graph[u].push_back(v);
				graph[v].push_back(u);
			}
		}
		dfs(1);

		std::cout << dp[1] << '\n';
	}
}