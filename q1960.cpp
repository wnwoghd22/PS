#include <iostream>
#include <vector>
#include <queue>

const int LEN = 1002;
const int INF = 1e9;

int c[LEN][LEN], f[LEN][LEN], d[LEN];
int N, source, sink, in, out;
std::vector<int> A[LEN];

int max_flow(const int source, const int sink) {
	int mf = 0;
	while (true) {
		std::fill(d, d + N * 2 + 2, -1);
		std::queue<int> q;
		q.push(source);

		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (const int& v : A[u]) {
				if (c[u][v] - f[u][v] > 0 && !~d[v]) {
					q.push(v);
					d[v] = u;
					if (v == sink) break;
				}
			}
		}
		if (!~d[sink]) break;

		int flow = INF;
		for (int i = sink; i ^ source; i = d[i]) flow = std::min(flow, c[d[i]][i] - f[d[i]][i]);
		for (int i = sink; i ^ source; i = d[i]) {
			f[d[i]][i] += flow;
			f[i][d[i]] -= flow;
		}
		mf += flow;
	}
	return mf;
}

int main() {
	std::cin >> N;
	source = N * 2, sink = N * 2 + 1;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			c[i][N + j] = 1;
			A[i].push_back(N + j);
			A[N + j].push_back(i);
		}
	}

	for (int _c, i = 0; i < N; ++i) {
		std::cin >> _c;
		c[source][i] = _c;
		A[source].push_back(i);
		A[i].push_back(source);
		in += _c;
	}
	for (int _c, i = 0; i < N; ++i) {
		std::cin >> _c;
		c[N + i][sink] = _c;
		A[N + i].push_back(sink);
		A[sink].push_back(N + i);
		out += _c;
	}

	int mf = max_flow(source, sink);
	if (mf == std::max(in, out)) {
		std::cout << 1 << '\n';
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j)
				std::cout << f[i][N + j];
			std::cout << '\n';
		}
	}
	else std::cout << -1;
}