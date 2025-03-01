#include <iostream>
#include <vector>
#include <queue>

const int MAX = 5010;
const int INF = 1e9;

int map[50][50], c[MAX][MAX], f[MAX][MAX], d[MAX][MAX]; // capacity, flow, distance(cost)
std::vector<int> a[MAX]; // adjacent graph
int const bottleneck = 5007, source = 5008, sink = 5009;
int N, K;
bool inQ[MAX];
int p[MAX], dist[MAX];

std::pair<int, int> MCMF(int source, int sink) {
	int mc = 0, mf = 0;

	while (true) {
		std::queue<int> q;
		std::fill(inQ, inQ + MAX, false);
		std::fill(p, p + MAX, 0);
		std::fill(dist, dist + MAX, INF);

		dist[source] = 0;
		q.push(source);
		inQ[source] = true;

		while (!q.empty()) {
			int u = q.front(); q.pop(); inQ[u] = false;
			for (const int& v : a[u]) { // u -> v
				if (c[u][v] - f[u][v] > 0 && dist[u] + d[u][v] < dist[v]) {
					dist[v] = dist[u] + d[u][v];
					p[v] = u;
					if (!inQ[v]) {
						inQ[v] = true;
						q.push(v), inQ[v] = true;
					}
				}
			}
		}
		if (!p[sink]) break;

		int flow = INF;

		for (int i = sink; i ^ source; i = p[i]) flow = std::min(flow, c[p[i]][i] - f[p[i]][i]);
		for (int i = sink; i ^ source; i = p[i]) {
			mc += flow * d[p[i]][i];
			f[p[i]][i] += flow;
			f[i][p[i]] -= flow;
		}
		mf += flow;
	}

	return { mc, mf };
}

void add_line(int s, int e, int cap, int dist) {
	a[s].push_back(e);
	a[e].push_back(s);
	c[s][e] = cap;
	d[s][e] = dist;
	d[e][s] = -dist;
}

int main() {
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> map[i][j];
			add_line(i * N + j + 1, i * N + j + 2501, 1, -map[i][j]);
		}
	}

	add_line(source, bottleneck, K, 0);
	add_line(bottleneck, 1, INF, 0);
	add_line(bottleneck, 2501, INF, 0);
	add_line(N * N + 2500, sink, INF, 0);

	for (int i = 0; i < N - 1; ++i) {
		for (int j = 0; j < N; ++j) {
			add_line(i * N + j + 2501, (i + 1) * N + j + 1, INF, 0);
			add_line(i * N + j + 2501, (i + 1) * N + j + 2501, INF, 0);
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N - 1; ++j) {
			add_line(i * N + j + 2501, i * N + j + 2, INF, 0);
			add_line(i * N + j + 2501, i * N + j + 2502, INF, 0);
		}
	}

	auto result = MCMF(source, sink);

	std::cout << -result.first;
}