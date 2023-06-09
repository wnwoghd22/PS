#include <iostream>
#include <vector>
#include <queue>

const int LEN = 100'001;

std::vector<int> graph[LEN];

int incoming[LEN];
int ord, order[LEN];
int level[LEN], cnt[LEN];
int max, num, critical[LEN];

int N, M;

void topological_sort() {
	std::queue<int> q;

	for (int u = 1; u <= N; ++u) {
		if (!incoming[u])
			q.push(u);
	}

	while (q.size()) {
		int u = q.front(); q.pop();
		++cnt[level[u]];
		order[ord++] = u;
		for (const int& v : graph[u]) {
			if (!--incoming[v]) {
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}
}

int main() {
	std::cin >> N >> M;
	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		++incoming[v];
	}
	topological_sort();

	for (int i = 0, m; i < N; ++i) {
		int u = order[i];
		if (cnt[level[u]] == 1 && max <= level[u]) critical[num++] = u;
		m = 1e9;
		for (const int& v : graph[u])
			m = std::min(m, level[v]);
		max = std::max(m, max);
	}
	std::cout << num << '\n';
	for (int i = 0; i < num; ++i) std::cout << critical[i] << ' ';
}