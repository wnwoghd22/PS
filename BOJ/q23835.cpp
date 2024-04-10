#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

typedef long long ll;
const int LEN = 1001;
std::vector<int> graph[LEN];
int N, Q, parent[LEN], level[LEN];
ll count[LEN];

void bfs(int u, int v) {
	memset(parent, -1, sizeof parent);
	std::queue<int> q;
	q.push(u);
	parent[u] = 0;
	level[u] = 0;
	while (q.size()) {
		int ui = q.front(); q.pop();
		if (ui == v) break;
		for (const int& vi : graph[ui]) {
			if (~parent[vi]) continue;
			level[vi] = level[ui] + 1;
			parent[vi] = ui;
			q.push(vi);
		}
	}
	for (int i = v; v ^ u; v = parent[v]) count[v] += level[v];
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 1, a, b; i < N; ++i) {
		std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	std::cin >> Q;
	for (int i = 0, t, u, v, x; i < Q; ++i) {
		std::cin >> t;
		if (t == 1) {
			std::cin >> u >> v;
			bfs(u, v);
		}
		if (t == 2) {
			std::cin >> x;
			std::cout << count[x] << '\n';
		}
	}
}