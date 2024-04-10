#include <iostream>
#include <queue>

const int LEN = 3001;
const int INF = 1e9 + 7;

int N, M, S, E, T;

int sum[LEN][LEN], x[LEN], dp[LEN][LEN];

struct Info { int u, w; } mins[LEN][3];
std::deque<Info> dq[LEN];

int get_min(int d, int v) {
	if (mins[d][0].u != v && mins[d][0].u != x[v]) return mins[d][0].w;
	if (mins[d][1].u != v && mins[d][1].u != x[v]) return mins[d][1].w;
	return mins[d][2].w;
}

void push_min(int d, int v, int w) {
	if (w < mins[d][0].w) mins[d][2] = mins[d][1], mins[d][1] = mins[d][0], mins[d][0] = { v, w };
	else if (w < mins[d][1].w) mins[d][2] = mins[d][1], mins[d][1] = { v, w };
	else mins[d][2] = { v, w };
}

int main() {
	std::cin >> N >> M >> S >> E >> T;
	for (int i = 1, A; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			std::cin >> A;
			sum[i][j] = A + sum[i][j - 1];
		}
	}
	for (int i = 1; i <= N; ++i) std::cin >> x[i];

	for (int d = 1; d <= M; ++d) {
		for (int i = 1; i <= N; ++i) {
			if (d >= S) {
				int min = get_min(d - S, i) - sum[i][d - S];
				while (dq[i].size() && dq[i].back().w >= min) dq[i].pop_back();
				dq[i].push_back({ d - S, min });
			}
			while (dq[i].size() && dq[i].front().u < d - E) dq[i].pop_front();
			if (dq[i].empty()) dp[d][i] = INF;
			else dp[d][i] = dq[i].front().w + T + sum[i][d];
		}
		mins[d][0] = mins[d][1] = mins[d][2] = { -1, INF };
		for (int i = 1; i <= N; ++i)
			if (dp[d][i] < INF)
				push_min(d, i, dp[d][i]);
	}
	for (int i = 1; i <= M; ++i) {
		for (int j = 1; j <= N; ++j)
			std::cout << dp[i][j] << ' ';
		std::cout << '\n';
	}
	int result = INF;
	for (int i = 1; i <= N; ++i) {
		for (int j = M - E; j < M; ++j) {
			int min = get_min(j, i);
			if (min >= INF) continue;
			result = std::min(result, min + sum[i][M] - sum[i][j]);
		}
	}
	std::cout << result;
}