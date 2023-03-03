#include <iostream>
#include <vector>
#include <queue>

typedef long long int ll;
const int INF = 1e9;
const int V_LEN = 1'001;
const int E_LEN = 30'000;

ll dp[V_LEN][V_LEN];
int N, M, K;
struct Edge { int v, w; };
std::vector<Edge> graph[V_LEN];
struct Info { 
	ll u, d, c; 
	bool operator<(const Info& r) const { return d > r.d; }
};

void dijkstra(int s) {
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			dp[i][j] = INF;
	std::priority_queue<Info> q;
	dp[s][0] = 0;
	q.push({ s, 0, 0 });
	while (q.size()) {
		Info i = q.top(); q.pop();
		for (const Edge& e : graph[i.u]) {
			if (dp[i.u][i.c] + e.w < dp[e.v][i.c + 1]) {
				dp[e.v][i.c + 1] = dp[i.u][i.c] + e.w;
				q.push({ e.v, dp[e.v][i.c + 1], i.c + 1 });
			}
		}
	}
}

// convex hull trick?
int main() {

}