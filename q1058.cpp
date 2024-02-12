#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

std::vector<int> g[50];
int visited[50];
int N, ret;

int bfs(int u) {
	memset(visited, -1, sizeof visited);
	int ret = 0;
	visited[u] = 0;
	
	std::queue<int> q;
	q.push(u);
	while (q.size()) {
		u = q.front(); q.pop();
		if (visited[u] == 2) continue;
		for (const int& v : g[u]) {
			if (~visited[v]) continue;
			visited[v] = visited[u] + 1;
			++ret;
			q.push(v);
		}
	}
	return ret;
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::string S;
		std::cin >> S;
		for (int j = 0; j < N; ++j) {
			if (S[j] == 'Y') g[i].push_back(j);
		}
	}
	for (int i = 0; i < N; ++i) {
		ret = std::max(ret, bfs(i));
	}
	std::cout << ret;
}