#include <iostream>
#include <vector>
#include <queue>

const int LEN = 100'001;

std::vector<int> graph[LEN];
bool visited[LEN];

int incoming[LEN];
int next[LEN];

int dfs(int u) {
	int cnt = 0;
	for (const int& v : graph[u]) {
		// if (visited[v]) next[u] += 
	}
}