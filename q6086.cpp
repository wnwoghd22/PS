#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>

const int INF = 1e9;
const int MAX = 256;

int N, M, U, V, source, sink;
int c[MAX][MAX], f[MAX][MAX];
int work[MAX], level[MAX];
std::vector<int> A[MAX];

bool bfs(int S, int T) {
	std::fill(level, level + MAX, -1);
	level[S] = 0;

	std::queue<int> q;
	q.push(S);

	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (const int& v : A[u]) {
			if (!~level[v] && c[u][v] - f[u][v] > 0) {
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}
	return ~level[T];
}

int dfs(int u, int T, int flow) {
	if (u == T) return flow;

	for (int& i = work[u]; i < A[u].size(); ++i) {
		int v = A[u][i];

		if (level[v] == level[u] + 1 && c[u][v] - f[u][v] > 0) {
			int ret = dfs(v, T, std::min(c[u][v] - f[u][v], flow));

			if (ret > 0) {
				f[u][v] += ret;
				f[v][u] -= ret;
				return ret;
			}
		}
	}
	return 0;
}

int dinic(int S, int T) {
	int totalFlow = 0;

	while (bfs(S, T)) {
		std::fill(work, work + MAX, 0);

		while (1) {
			int flow = dfs(S, T, INF);
			if (flow == 0)
				break;
			totalFlow += flow;
		}
	}

	return totalFlow;
}

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;

	char u, v;
	for (int i = 0, cap; i < N; ++i) {
		std::cin >> u >> v >> cap;
		c[u][v] = c[v][u] += cap;
		A[u].push_back(v);
		A[v].push_back(u);
	}
	std::cout << dinic('A', 'Z');
}