#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

const int MAX = 102;
const double INF = 2e9;

int N, M, source, sink;
double c[MAX][MAX], f[MAX][MAX]; // capacity, flow
int d[MAX];
std::vector<int> A[MAX];
int sp, result[MAX];

int max_flow(const int start, const int end, const double g) { // guess
	memset(f, 0, sizeof f);
	for (int i = 1; i <= N; ++i)
		c[i][sink] = M + 2 * g - (A[i].size() - 2);

	while (1) {
		std::fill(d, d + MAX, -1);
		std::queue<int> q;
		q.push(start);

		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (const int& v : A[u]) {
				if (c[u][v] - f[u][v] > 0 && !~d[v]) {
					q.push(v);
					d[v] = u;
					if (v == end) break;
				}
			}
		}
		if (!~d[end]) break;

		double flow = INF;
		for (int i = end; i ^ start; i = d[i]) {
			flow = std::min(flow, c[d[i]][i] - f[d[i]][i]);
		}
		for (int i = end; i ^ start; i = d[i]) {
			f[d[i]][i] += flow;
			f[i][d[i]] -= flow;
		}
	}
	int count = 0;
	for (int i = 1; i <= N; ++i) {
		if (~d[i])
			++count;
	}
	return count;
}

int binary_search() {
	double l = 0, r = M, m, max = 0;
	while (r - l >= 1.0 / (N * (N - 1))) {
		m = (l + r) / 2;
		int v = max_flow(source, sink, m);
		if (v > 0) {
			l = m;
			if (m > max) {
				max = m;
				sp = 0;
				for (int i = 1; i <= N; ++i) {
					if (~d[i])
						result[sp++] = i;
				}
			}
		}
		else r = m;
	}
	return sp;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	if (M == 0) {
		std::cout << "1\n1\n";
		return 0;
	}
	source = 0, sink = N + 1;

	for (int i = 1; i <= N; ++i) {
		A[source].push_back(i);
		A[i].push_back(source);
		c[source][i] = M;
		A[sink].push_back(i);
		A[i].push_back(sink);
	}

	int u, v;
	for (int i = 0; i < M; ++i) {
		std::cin >> u >> v;
		A[u].push_back(v);
		A[v].push_back(u);
		c[u][v] = c[v][u] = 1;
	}

	std::cout << binary_search() << '\n';
	for (int i = 0; i < sp; ++i)
		std::cout << result[i] << '\n';
}