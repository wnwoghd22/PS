#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long ll;
const int LEN = 200'001;
const ll INF = 1ll << 62;

struct E {
	int v, w;
};

std::vector<E> graph[LEN];

struct Info {
	ll w;
	int u;
	bool operator<(const Info& o) const {
		return w > o.w;
	}
};

int N, M;
ll dp[LEN];
ll cost[LEN];

ll dijkstra() {
	for (int i = 1; i <= N; ++i) dp[i] = INF;
	dp[1] = 0;
	std::priority_queue<Info> pq;
	pq.push({ 0, 1 });

	while (pq.size()) {
		int u = pq.top().u;
		int w = pq.top().w;
		pq.pop();
		if (w > dp[u]) continue;
		for (const E& e : graph[u]) {
			int v = e.v;
			ll c = e.w;
			if (w + c < dp[v]) {
				dp[v] = w + c;
				cost[v] = w * 9 + c * 10;
				pq.push({ dp[v], v });
			}
			else if (w + c == dp[v]) {
				cost[v] = std::min(cost[v], w * 9 + c * 10);
			}
		}
	}
	ll ret = 0;
	for (int i = 2; i <= N; ++i) ret += cost[i];
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 0, a, b, c; i < M; ++i) {
		std::cin >> a >> b >> c;
		graph[a].push_back({ b, c / 10 });
		graph[b].push_back({ a, c / 10 });
	}
	ll ret = dijkstra();
	std::cout << ret;
}