#include <iostream>
#include <vector>
#include <queue>

std::vector<int> g[51];
std::priority_queue<int> pq[51];

int dfs(int u) {
	int c = 0, ret = 0;
	for (const int& v : g[u]) pq[u].push(dfs(v));
	while (pq[u].size()) {
		ret = std::max(ret, pq[u].top() + c++);
		pq[u].pop();
	}
	return ret + 1;
}

int N, p;

int main() {
	std::cin >> N >> p;
	for (int i = 1; i < N; ++i) {
		std::cin >> p;
		g[p].push_back(i);
	}
	std::cout << dfs(0) - 1;
}