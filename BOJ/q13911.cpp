#include <iostream>
#include <vector>
#include <queue>

const int LEN = 10'001;
const int INF = 1e9 + 7;

struct Edge { 
	int v, w;
	bool operator<(const Edge& r) const { return w > r.w; }
};
std::vector<Edge> g[LEN];
std::priority_queue<Edge> pq;

int V, E;
bool f[LEN];
int x[2], d[2][LEN];

int main() {
	std::cin >> V >> E;
	for (int i = 0, u, v, w; i < E; ++i) {
		std::cin >> u >> v >> w;
		g[u].push_back({ v, w });
		g[v].push_back({ u, w });
	}
	for (int k = 0, n; k < 2; ++k) {
		std::cin >> n >> x[k];
		for (int u = 1; u <= V; ++u) d[k][u] = INF;
		for (int i = 0, m; i < n; ++i) {
			std::cin >> m;
			pq.push({ m, 0 });
			d[k][m] = 0;
			f[m] = 1;
		}
		while (pq.size()) {
			int u = pq.top().v, w = pq.top().w; pq.pop();
			if (w > d[k][u]) continue;
			for (const Edge& e : g[u]) {
				if (d[k][u] + e.w < d[k][e.v]) {
					d[k][e.v] = d[k][u] + e.w;
					pq.push({ e.v, d[k][e.v] });
				}
			}
		}
	}
	int ret = INF;
	for (int u = 1; u <= V; ++u) {
		if (!f[u] && d[0][u] <= x[0] && d[1][u] <= x[1])
			ret = std::min(ret, d[0][u] + d[1][u]);
	}
	std::cout << (ret < INF ? ret : -1);
}