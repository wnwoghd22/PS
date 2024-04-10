#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 500'001;
std::vector<int> graph[LEN];
int degree[LEN], checked[LEN];
int N, result;

void dfs(int u, int mask) {
	checked[u] = mask;
	for (const int& v : graph[u]) {
		if (!checked[v] && degree[v] == 2)
			dfs(v, mask);
	}
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1, a, b; i < N; ++i) {
		std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
		degree[a]++;
		degree[b]++;
	}

	for (int d = 1; d <= 2; ++d) {
		for (int u = 1; u <= N; ++u)
			if (!checked[u] && degree[u] == 1) {
				checked[u] = d;
				for (const int& v : graph[u])
					if (!checked[v] && degree[v] == 2)
						dfs(v, d);
			}

		for (int u = 1; u <= N; ++u)
			if (checked[u] == d)
				for (const int& v : graph[u])
					--degree[v];
	}

	for (int i = 1; i <= N; ++i)
		if (!checked[i] && degree[i] > 2)
			result = 1;

	std::cout << (result ? "NO" : "YES");
}
