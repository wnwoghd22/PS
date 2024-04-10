#include <iostream>
#include <algorithm>

const int LEN = 100'000;
int N, dp[LEN][2], host[LEN], protocol[LEN];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> dp[i][1];
	for (int i = 1; i < N; ++i) std::cin >> host[i] >> protocol[i];
	for (int i = N - 1; i; --i) {
		if (protocol[i] == 0) {
			dp[host[i]][1] += dp[i][0];
			dp[host[i]][0] += std::max(dp[i][0], dp[i][1]);
		}
		if (protocol[i] == 1) {
			dp[host[i]][1] += dp[i][1];
			dp[host[i]][1] = std::max(dp[host[i]][0] + dp[i][1], dp[host[i]][1] + dp[i][0]);
			dp[host[i]][0] += dp[i][0];
		}
		if (protocol[i] == 2) {
			// dp[host[i]][1] += dp[i][1];
			dp[host[i]][1] = std::max(dp[host[i]][0] + dp[i][1], dp[host[i]][1] + dp[i][0]);
			dp[host[i]][0] += dp[i][0];
		}
	}
	// for (int i = 0; i < N; ++i) std::cout << dp[i][0] << ' '; std::cout << '\n';
	// for (int i = 0; i < N; ++i) std::cout << dp[i][1] << ' '; std::cout << '\n';

	std::cout << std::max(dp[0][0], dp[0][1]);
}
