#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <cassert>

const int LEN = 101;
const int N_LEN = 1001;
const int M_LEN = 10001;
const int INF = 1e9 + 7;
const double EPS = 1e-7;

struct E {
	int u, c;
	double d;
	bool operator<(const E& r) const {
		return abs(d - r.d) < EPS ? c > r.c : d > r.d;
	}
};

int H, W, R, S, N, M;
double dp[N_LEN][M_LEN];
char map[LEN][LEN];
int x[N_LEN], y[N_LEN], dif[N_LEN];

std::vector<E> graph[N_LEN];
std::priority_queue<E> pq;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> H >> W >> R >> S;
	for (int i = 0; i < H; ++i) {
		std::cin >> map[i];
		for (int j = 0; j < W; ++j) {
			if (map[i][j] != '.') {
				N++;
				x[N] = i; y[N] = j; dif[N] = map[i][j] - '0';
			}
		}
	}
	M = std::min(N * 9, S);
	assert(M <= 6260);

	for (int i = 1; i <= N; ++i)
		for (int j = 0; j <= M; ++j)
			dp[i][j] = INF;

	for (int u = 1; u <= N; ++u) {
		for (int v = 1; v <= N; ++v) {
			if (u == v) continue;
			int dx = x[u] - x[v];
			int dy = y[u] - y[v];
			if (dx * dx + dy * dy <= R * R) {
				graph[u].push_back({ v, dif[v], sqrt(dx * dx + dy * dy) });
			}
		}
	}
	for (int i = 1; i <= N; ++i) std::sort(graph[i].begin(), graph[i].end());
	for (int i = 0; i <= M; ++i) dp[N][i] = dif[N];
	pq.push({ N, dif[N], 0});
	while (pq.size()) {
		int u = pq.top().u;
		int m = pq.top().c;
		double dist = pq.top().d;
		 pq.pop();
		
		if (u == 1) continue;
		if (dist > dp[u][m]) continue;
		for (int i = graph[u].size() - 1; i >= 0; --i) {
			const E& e = graph[u][i];
			int v = e.u, c = m + e.c;
			double d = dist + e.d;
			if (c > M) continue;
			if (dp[v][c] > d) {
				dp[v][c] = d;
				for (int k = c + 1; k <= M; ++k) {
					if (dp[v][k] < d) break;
					dp[v][k] = d;
				}
				pq.push({ v, c, d });
			}
		}
	}
	double result = INF;
	for (int c = 0; c <= M; ++c)
		if (dp[1][c] < result)
			result = dp[1][c];

	std::cout << std::fixed;
	std::cout.precision(9);
	if (result > INF - 1) std::cout << "impossible";
	else std::cout << result;
}