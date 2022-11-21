#include <iostream>
#include <vector>
#include <queue>

const int MAX = 1003;
const int INF = 1e9;

int c[MAX][MAX], f[MAX][MAX], d[MAX][MAX]; // capacity, flow, distance(cost)
std::vector<int> a[MAX]; // adjacent graph
int const source = 1001, sink = 1002;
int T, N, M, x, y;
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

int main() {
	std::cin >> T;
	while (T--) {
		memset(c, 0, sizeof c);
		memset(d, 0, sizeof d);
		memset(f, 0, sizeof f);
		for (std::vector<int> v : a) v.clear();

		std::cin >> N >> M;

		for (int i = 1; i <= N; ++i) {
			a[i].push_back(i + 500);
			a[i + 500].push_back(i);
			c[i][i + 500] = INF;
		}

		while (M--) {
			std::cin >> x >> y;
			a[x + 500].push_back(y), a[y + 500].push_back(x);
			a[x].push_back(y + 500); a[y].push_back(x + 500);
			d[x + 500][y] = d[y + 500][x] = 1;
			d[x][y + 500] = d[y][x + 500] = -1;
			c[x + 500][y] = c[y + 500][x] = INF;
		}
		for (int i = 1; i <= N; ++i) {
			std::cin >> x;
			if (x) {
				a[source].push_back(i);
				a[i].push_back(source);
				c[source][i] = 1;
			}
		}
		for (int i = 1; i <= N; ++i) {
			std::cin >> x;
			if (x) {
				a[sink].push_back(i + 500);
				a[i + 500].push_back(sink);
				c[i + 500][sink] = 1;
			}
		}

		auto result = MCMF(source, sink);

		std::cout << result.first << '\n';
	}
}