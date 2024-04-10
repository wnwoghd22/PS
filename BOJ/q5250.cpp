#include <iostream>
#include <algorithm>
#include <queue>

const int V_LEN = 2001;
const int LEN = 1e5 + 1;
const int INF = 1e9 + 7;
struct Edge {
	int v, d;
	bool operator<(const Edge& r) const { return d > r.d; }
};

int N, M, K, S, E;
int lucky[V_LEN];
std::vector<Edge> graph[V_LEN];

int dist_s[V_LEN], dist_e[V_LEN];
void dijkstra(int s, int* dist) {
	std::priority_queue<Edge> pq;
	for (int i = 1; i <= N; ++i) dist[i] = INF;
	dist[s] = 0;
	pq.push({ s, 0 });
	while (pq.size()) {
		int u = pq.top().v, d = pq.top().d; pq.pop();
		if (d > dist[u]) continue;
		for (const Edge& e : graph[u]) {
			if (d + e.d < dist[e.v])
				pq.push({ e.v, dist[e.v] = d + e.d });
		}
	}
}

int lucky_s[V_LEN], lucky_e[V_LEN];
void dfs(int* lucky_p, int* dist, int u, int p) {
	if (lucky_p[u]) return;
	if (lucky[u]) p = u;
	lucky_p[u] = p;

	for (const Edge& e : graph[u]) {
		if (dist[u] + e.d ^ dist[e.v]) continue;
		if (!lucky[u] && lucky[e.v]) continue;
		dfs(lucky_p, dist, e.v, p);
	}
}

int seg_min[V_LEN << 2];
void update(int l, int r, int d, int s = 1, int e = K - 1, int i = 1) {
	if (r < s || e < l) return;
	if (l <= s && e <= r) { seg_min[i] = std::min(seg_min[i], d); return; }
	int m = s + e >> 1;
	update(l, r, d, s, m, i << 1); update(l, r, d, m + 1, e, i << 1 | 1);
}
int get_min(int x, int s = 1, int e = K - 1, int i = 1) {
	if (x < s || e < x) return INF;
	if (s == e) return seg_min[i];
	int m = s + e >> 1;
	return std::min({ seg_min[i], get_min(x, s, m, i << 1), get_min(x, m + 1, e, i << 1 | 1) });
}

int main() {
	std::cin >> N >> M >> S >> E;
	for (int i = 0, u, v, w; i < M; ++i) {
		std::cin >> u >> v >> w;
		graph[u].push_back({ v, w });
		graph[v].push_back({ u, w });
	}
	std::cin >> K;
	for (int i = 1, u; i <= K; ++i) std::cin >> u, lucky[u] = i;

	dijkstra(S, dist_s); dijkstra(E, dist_e);
	dfs(lucky_s, dist_s, S, S); dfs(lucky_e, dist_e, E, E);

	for (int i = 1; i <= (N << 2); ++i) seg_min[i] = INF;
	for (int u = 1; u <= N; ++u) {
		for (const Edge& e : graph[u]) {
			if (lucky[u] && lucky[e.v] && std::abs(lucky[e.v] - lucky[u]) <= 1) continue;
			int lu = lucky[lucky_s[u]];
			int lv = lucky[lucky_e[e.v]];
			update(lu, lv - 1, dist_s[u] + e.d + dist_e[e.v]);
		}
	}
	for (int i = 1; i < K; ++i) {
		int d = get_min(i);
		std::cout << (d == INF ? -1 : d) << '\n';
	}
}