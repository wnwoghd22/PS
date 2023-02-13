#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int LEN = 102;
const int INF = 1e9;

int c[LEN][LEN], f[LEN][LEN], d[LEN];
int N, M, source, sink, in, out;
std::vector<int> graph[LEN];

int max_flow(const int source, const int sink) {
	int mf = 0;
	while (true) {
		memset(d, -1, sizeof d);
		std::queue<int> q;
		q.push(source);

		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (const int& v : graph[u]) {
				if (c[u][v] - f[u][v] > 0 && !~d[v]) {
					q.push(v);
					d[v] = u;
				}
				if (v == sink) break;
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
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	source = N + M, sink = source + 1;
	for (int i = 0; i < N; ++i) {
		std::cin >> c[source][i];
		graph[source].push_back(i);
		in += c[source][i];
	}
	for (int i = 0; i < M; ++i) {
		std::cin >> c[N + i][sink];
		graph[N + i].push_back(sink);
		out += c[N + i][sink];
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			c[i][N + j] = 1;
			graph[i].push_back(N + j);
		}
	}
	int mf = max_flow(source, sink);
	if (in == out && out == mf) {

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j)
				std::cout << f[i][N + j];
			std::cout << '\n';
		}
	}
	else std::cout << -1;
}