#include <iostream>
#include <algorithm>
#include <cstring>

const int INF = 1e9;
int arr[2][10'001];
int dp[10'001][3]; // 0: vertical, 1: up, 2: down
int N, W;

void f() {
	for (int i = 2; i <= N; ++i) {
		int upH = arr[0][i - 1] + arr[0][i] > W ? 2 : 1;
		int downH = arr[1][i - 1] + arr[1][i] > W ? 2 : 1;
		int V = arr[0][i] + arr[1][i] > W ? 2 : 1;

		dp[i][0] = std::min({ dp[i - 1][0] + V, dp[i - 2][0] + upH + downH, dp[i - 1][1] + downH + 1, dp[i - 1][2] + upH + 1 });
		dp[i][1] = std::min(dp[i - 1][0] + 1, dp[i - 1][2] + upH);
		dp[i][2] = std::min(dp[i - 1][0] + 1, dp[i - 1][1] + downH);
	}
}

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		memset(dp, 0, sizeof dp);

		std::cin >> N >> W;

		for (int i = 0; i < 2; ++i)
			for (int j = 1; j <= N; ++j)
				std::cin >> arr[i][j];

		if (N < 2) {
			std::cout << (arr[0][1] + arr[1][1] > W ? 2 : 1) << '\n';
			continue;
		}

		int costUp = arr[0][1], costDown = arr[1][1], result = INF;

		// no merge
		dp[1][0] = arr[0][1] + arr[1][1] > W ? 2 : 1;
		dp[1][1] = dp[1][2] = 1;
		f();
		result = std::min(result, dp[N][0]);

		// merge upH ((0,1) - (0,N))
		if (arr[0][1] + arr[0][N] <= W) { // if can merge
			arr[0][1] = INF;
			dp[1][0] = 2; // (0,1) and (1,1) seperated
			dp[1][1] = dp[1][2] = 1;
			f();
			result = std::min(result, dp[N][2]);
			arr[0][1] = costUp;
		}
		// merge downH ((1,1) - (1,N))
		if (arr[1][1] + arr[1][N] <= W) { // if can merge
			arr[1][1] = INF;
			dp[1][0] = 2; // (0,1) and (1,1) seperated
			dp[1][1] = dp[1][2] = 1;
			f();
			result = std::min(result, dp[N][1]);
			arr[1][1] = costDown;
		}

		// merge upH and downH
		if (arr[0][1] + arr[0][N] <= W && arr[1][1] + arr[1][N] <= W) { // if can merge
			arr[0][1] = arr[1][1] = INF;
			dp[1][0] = 2; // (0,1) and (1,1) seperated
			dp[1][1] = dp[1][2] = 1;
			f();
			result = std::min(result, dp[N - 1][0]);
			arr[0][1] = costUp;
			arr[1][1] = costDown;
		}

		std::cout << result << '\n';
	}
}