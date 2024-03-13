#include <iostream>
#include <vector>
#include <queue>

const int LEN = 50'001;
const int INF = 1e9 + 7;

struct E { 
	int v, w;
	bool operator<(const E& r) const { return w > r.w; }
};
std::vector<E> g[LEN];
std::priority_queue<E> pq;
int N, M, d[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 0, u, v, w; i < M; ++i) {
		std::cin >> u >> v >> w;
		g[u].push_back({ v, w });
		g[v].push_back({ u, w });
	}
	for (int i = 2; i <= N; ++i) d[i] = INF;
	pq.push({ 1, 0 });
	while (pq.size()) {
		int u = pq.top().v;
		int w = pq.top().w;
		pq.pop();
		if (w > d[u]) continue;
		for (const E& e : g[u]) {
			if (d[u] + e.w < d[e.v]) {
				d[e.v] = d[u] + e.w;
				pq.push({ e.v, d[e.v] });
			}
		}
	}
	std::cout << d[N];
}