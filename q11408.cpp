#include <iostream>
#include <vector>
#include <queue>

const int MAX = 803;
const int INF = 1e9;

int c[MAX][MAX], f[MAX][MAX], d[MAX][MAX]; // capacity, flow, distance(cost)
std::vector<int> a[MAX]; // adjacent graph
int source = 801, sink = 802;
int N, M;

std::pair<int, int> MCMF(int source, int sink) {
	int mc = 0, mf = 0;

	while (true) {
		bool inQ[MAX] = {};
		std::queue<int> q;
		int p[MAX] = {}, dist[MAX];
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

int main() {
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		a[source].push_back(i);
		a[i].push_back(source);
		c[source][i] = 1;
	}
	for (int i = 1; i <= M; ++i) {
		a[N + i].push_back(sink);
		a[sink].push_back(N + i);
		c[N + i][sink] = 1;
	}
	for (int K, v, dst, u = 1; u <= N; ++u) {
		std::cin >> K;
		while (K--) {
			std::cin >> v >> dst;
			a[u].push_back(v + N);
			a[v + N].push_back(u);
			d[u][v + N] = dst, d[v + N][u] = -dst;
			c[u][v + N] = 1;
		}
	}
	auto result = MCMF(source, sink);

	std::cout << result.second << '\n' << result.first;
}