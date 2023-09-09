#include <iostream>
#include <vector>
#include <queue>
#include <map>

typedef long long ll;
const int LEN = 50001;

struct I {
	ll d;
	int w;
	int u;
	bool operator<(const I& r) const {
		return d == r.d ? w > r.w : d > r.d;
	}
};
struct Ed { int v, w; };

std::priority_queue<I> pq;
std::vector<Ed> graph[LEN];
std::map<int, ll> dist[LEN];

int N, M, S, E;

int main() {
	std::cin >> N >> M;
	for (int i = 0, u, v, w; i < M; ++i) {
		std::cin >> u >> v >> w;
		graph[u].push_back({ v, w });
		graph[v].push_back({ u, w });
	}
	std::cin >> S >> E;

	dist[S][0] = 0;
	pq.push({ 0, 0, S });
	while (pq.size()) {
		int u = pq.top().u, w = pq.top().w;
		ll d = pq.top().d; pq.pop();
		if (dist[u][w] < d) continue;

		for (const Ed& e : graph[u]) {
			if (e.w <= w) continue;
			if (dist[e.v].find(e.w) == dist[e.v].end() || dist[e.v][e.w] < d + e.w) {
				dist[e.v][e.w] = d + e.w;
				pq.push({ d + e.w, e.w, e.v });
			}
		}
	}
	if (dist[E].empty()) std::cout << "DIGESTA";
	else {
		ll min = 1e17;
		for (const auto&[k, v] : dist[E]) {
			min = std::min(min, v);
		}
		std::cout << min;
	}
}