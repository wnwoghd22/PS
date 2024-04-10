#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

const int LEN = 5001;

std::vector<int> g[LEN];
int N, M, incoming[LEN], depth[LEN];

bool t_sort() {
	int ret = 0;
	std::queue<int> q;
	for (int u = 1; u <= N; ++u) {
		if (!incoming[u]) {
			q.push(u);
			depth[u] = 1;
		}
	}
	while (q.size()) {
		int u = q.front(); q.pop();
		std::cout << u << '\n';
		for (const int& v : g[u]) {
			depth[v] = std::max(depth[v], depth[u] + 1);
			ret = std::max(ret, depth[v]);
			if (!--incoming[v]) {
				q.push(v);
			}
		}
	}
	return ret < N;
}

int main() {
	std::cin >> N >> M;
	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		g[u].push_back(v);
		incoming[v]++;
	}
	std::cout << t_sort();
}