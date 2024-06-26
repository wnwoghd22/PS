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
		std::fill(d, d + MAX, -1);
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

	for (int i = 1; i <= N; ++i) {
		A[i].push_back(i + 400);
		A[i + 400].push_back(i);
		c[i][i + 400] = 1;
	}

	int u, v;
	while (P--) {
		std::cin >> u >> v;

		A[u + 400].push_back(v);
		A[v].push_back(u + 400);
		c[u + 400][v] = 1;

		A[v + 400].push_back(u);
		A[u].push_back(v + 400);
		c[v + 400][u] = 1;
	}

	std::cout << max_flow(401, 2);
}