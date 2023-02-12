#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

const int LEN = 201;
const int INF = 1e9;
struct Edge { int v, l; };
struct Info {
	int u, d;
	bool operator<(const Info& r) const { return d > r.d; }
};
std::vector<Edge> graph[LEN];
int N, M, S, E, L, dist[LEN];

double dijkstra(int s) {
	std::priority_queue<Info> pq;
	for (int i = 1; i <= N; ++i) dist[i] = INF;
	double result = 0;
	dist[s] = 0;
	pq.push({ s, 0 });
	while (pq.size()) {
		auto [u, d] = pq.top(); pq.pop();
		// std::cout << "dijkstra u: " << u << ", dist: " << d << '\n';
		if (d > dist[u]) {
			result = std::max(result, ((double)d + dist[u]) / 2);
			continue;
		}
		result = std::max(result, (double)d);
		for (const auto& [v, l] : graph[u]) {
			if (u == v) {
				result = std::max(result, d + (double)l / 2);
				continue;
			}
			dist[v] = std::min(dist[v], d + l);
			pq.push({ v, d + l });
		}
	}
	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	while (M--) {
		std::cin >> S >> E >> L;
		graph[S].push_back({ E, L });
		graph[E].push_back({ S, L });
	}
	double min = 1e9;
	std::cout << std::fixed;
	std::cout.precision(1);
	for (int u = 1; u <= N; ++u) min = std::min(min, dijkstra(u));
	std::cout << min;
}