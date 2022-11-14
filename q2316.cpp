#include <iostream>
#include <vector>
#include <queue>

const int MAX = 801;
const int INF = 1e9;

int N, P;
int c[MAX][MAX], f[MAX][MAX]; // capacity, flow
int d[MAX];
std::vector<int> A[MAX];

int max_flow(const int start, const int end) {
	int result = 0;
	while (1) {
		std::fill(d, d + N * 2 - 1, -1);
		std::queue<int> q;
		q.push(start);

		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (const int& u : A[v]) {
				if (c[v][u] - f[v][u] > 0 && !~d[u]) {
					q.push(u);
					d[u] = v;
					if (u == end) break;
				}
			}
		}
		if (!~d[end]) break;

		int flow = INF;
		for (int i = end; i != start; i = d[i]) {
			flow = std::min(flow, c[d[i]][i] - f[d[i]][i]);
		}
		for (int i = end; i != start; i = d[i]) {
			f[d[i]][i] += flow;
			f[i][d[i]] -= flow;
		}
		result += flow;
	}
	return result;
}

int main() {
	std::cin >> N >> P;

	for (int i = 3; i <= N; ++i) {
		A[i].push_back(i + N - 2);
		A[i + N - 2].push_back(i);
		c[i][i + N - 2] = 1;
	}

	int u, v;
	while (P--) {
		std::cin >> u >> v;
		if (u != 1) u = u + N - 2;
		A[u].push_back(v);
		A[v].push_back(u);
		c[u][v] = 1;
	}

	std::cout << max_flow(1, 2);
}