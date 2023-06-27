#include <iostream>
#include <vector>
#include <queue>
#include <map>

const int LEN = 5'001;
const int INF = 1e9;

std::map<int, int> weight[LEN];
std::vector<int> graph[LEN];

struct Info {
	int u, d;
	bool operator<(const Info& r) const {
		return d > r.d;
	}
};
std::priority_queue<Info> pq;

int dist[LEN], mask[LEN];
int dist_inv[LEN], mask_inv[LEN], p[LEN];

int N, M;

int main() {
	std::cin >> N >> M;
	for (int i = 0, a, b, c, d; i < M; ++i) {
		std::cin >> a >> b >> c >> d;
		graph[a].push_back(b);
		graph[b].push_back(a);
		weight[a][b] = c;
		weight[b][a] = d;
	}
	for (int i = 1; i <= N; ++i) dist[i] = INF;
	mask[1] = 1; dist[1] = 0;
	for (const int& v : graph[1]) {
		mask[v] = v;
		dist[v] = weight[1][v];
		pq.push({ v, dist[v] });
	}
	while (pq.size()) {
		int u = pq.top().u, d = pq.top().d; pq.pop();
		if (dist[u] < d) continue;

		for (const int& v : graph[u]) {
			if (dist[u] + weight[u][v] < dist[v]) {
				mask[v] = mask[u];
				dist[v] = dist[u] + weight[u][v];
				pq.push({ v, dist[v] });
			}
		}
	}

	int result = INF;
	for (int i = 1; i <= N; ++i) dist_inv[i] = INF;
	mask_inv[1] = 1; dist_inv[1] = 0;
	for (const int& v : graph[1]) {
		mask_inv[v] = v; p[v] = 1;
		dist_inv[v] = weight[v][1];
		if (mask_inv[v] != mask[v])
			result = std::min(result, dist[v] + dist_inv[v]);
		pq.push({ v, dist_inv[v] });
	}
	while (pq.size()) {
		int u = pq.top().u, d = pq.top().d; pq.pop();
		if (dist_inv[u] < d) continue;
		if (mask_inv[u] != mask[u])
			result = std::min(result, dist[u] + dist_inv[u]);

		for (const int& v : graph[u]) {
			if (mask[v] != mask_inv[u] && p[u] != v)
				result = std::min(result, dist[v] + weight[v][u] + dist_inv[u]);
			
			if (dist_inv[u] + weight[v][u] < dist_inv[v]) {
				mask_inv[v] = mask_inv[u]; p[v] = u;
				dist_inv[v] = dist_inv[u] + weight[v][u];
				pq.push({ v, dist_inv[v] });
			}
		}
	}
	std::cout << result;
}
