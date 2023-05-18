#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 500'001;
std::vector<int> graph[LEN];
int degree[LEN], checked[LEN];
int N, result;

int main() {
	std::cin >> N;
	for (int i = 1, a, b; i < N; ++i) {
		std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
		degree[a]++;
		degree[b]++;
	}
	for (int i = 1; i <= N; ++i) checked[i] = degree[i] == 1;
	for (int u = 1; u <= N; ++u)
		if (checked[u])
			for (const int& v : graph[u])
				--degree[v];
	
	for (int i = 1; i <= N; ++i) {
		if (!checked[i] && degree[i] == 1)
			checked[i] = 2;
	}
	for (int u = 1; u <= N; ++u)
		if (checked[u] == 2)
			for (const int& v : graph[u])
				--degree[v];
	
	for (int i = 1; i <= N; ++i)
		if (!checked[i] && degree[i] > 2)
			result = 1;

	std::cout << (result ? "NO" : "YES");
}
