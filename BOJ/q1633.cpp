#include <iostream>
#include <vector>
#include <queue>

const int MAX = 1005;
const int INF = 1e9;

int c[MAX][MAX], f[MAX][MAX], d[MAX][MAX]; // capacity, flow, distance(cost)
std::vector<int> a[MAX]; // adjacent graph
int const W = 1, B = 2, source = 3, sink = 4;
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
	/* int w, b, i = 5;
	while (std::cin >> w >> b) {
		a[source].push_back(i);
		a[i].push_back(source);
		c[source][i] = 1;

		a[i].push_back(W), a[W].push_back(i);
		a[i].push_back(B), a[B].push_back(i);
		c[i][W] = 1, c[i][B] = 1;

		d[i][W] = -w, d[W][i] = w;
		d[i][B] = -b, d[B][i] = b;
	} */
	for (int w, b, i = 5; i <= 30; ++i) {
		a[source].push_back(i);
		a[i].push_back(source);
		c[source][i] = 1;

		a[i].push_back(W), a[W].push_back(i);
		a[i].push_back(B), a[B].push_back(i);
		c[i][W] = 1, c[i][B] = 1;

		std::cin >> w >> b;
		d[i][W] = -w, d[W][i] = w;
		d[i][B] = -b, d[B][i] = b;
	}
	a[W].push_back(sink), a[sink].push_back(W);
	a[B].push_back(sink), a[sink].push_back(B);
	c[W][sink] = 15, c[B][sink] = 15;

	auto result = MCMF(source, sink);

	std::cout << -result.first;
}