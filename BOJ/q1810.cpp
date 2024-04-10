#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <map>

typedef long long ll;
typedef long double ld;
const int MAX = 1'000'001;
const int LEN = 50'001;
const ld INF = 2e18;

std::map<int, int> map[MAX];

struct Edge {
	int v;
	ld d;
	bool operator<(const Edge& r) const {
		return d > r.d;
	}
};

ld distance(int x1, int y1, int x2, int y2) { return std::sqrt((ld)(x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)); }

ld dist[LEN];
std::priority_queue<Edge> pq;
std::vector<Edge> graph[LEN];
int N, F, x[LEN], y[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> F;
	for (int i = 1; i <= N; ++i) {
		std::cin >> x[i] >> y[i];
		map[y[i]][x[i]] = i;
	}
	map[0][0] = 0;

	for (int u = 0; u <= N; ++u) {
		for (int i = std::max(y[u] - 2, 0); i <= std::min(y[u] + 2, F); ++i) {
			for (int j = x[u] - 2; j <= x[u] + 2; ++j) {
				if (i == y[u] && j == x[u]) continue;
				if (map[i].find(j) != map[i].end()) {
					int v = map[i][j];
					graph[u].push_back({ v, distance(y[u], x[u], i, j) });
				}
			}
		}
	}

	for (int i = 1; i <= N; ++i) dist[i] = INF;
	dist[0] = 0;
	pq.push({ 0, 0 });
	while (pq.size()) {
		int u = pq.top().v;
		ld d = pq.top().d;
		pq.pop();
		if (d > dist[u]) continue;

		for (const Edge& e : graph[u]) {
			if (d + e.d < dist[e.v]) {
				dist[e.v] = d + e.d;
				pq.push({ e.v, dist[e.v] });
			}
		}
	}
	ld result = INF;
	for (int i = 0; i <= N; ++i) {
		if (y[i] == F)
			result = std::min(dist[i], result);
	}
	ll answer = -1;
	if (result < INF) {
		answer = result * 10 + 5;
		answer /= 10;
	}
	std::cout << answer;
}