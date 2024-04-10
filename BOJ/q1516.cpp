#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int LEN = 501;

std::vector<int> graph[LEN];
int N, incoming[LEN], t[LEN], d[LEN];

void tsort() {
	std::queue<int> q;
	for (int u = 1; u <= N; ++u) {
		if (!incoming[u]) {
			d[u] = t[u];
			q.push(u);
		}
	}
	while (q.size()) {
		int u = q.front(); q.pop();
		for (const int& v : graph[u]) {
			d[v] = std::max(d[v], d[u] + t[v]);
			if (!--incoming[v]) q.push(v);
		}
	}
}

int main() {
	std::cin >> N;
	for (int u, v = 1; v <= N; ++v) {
		std::cin >> t[v];
		while (1) {
			std::cin >> u;
			if (!~u) break;
			graph[u].push_back(v);
			incoming[v]++;
		}
	}
	tsort();
	for (int u = 1; u <= N; ++u) std::cout << d[u] << '\n';
}