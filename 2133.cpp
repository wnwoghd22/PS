#include <iostream>

typedef long long ll;

ll N, i, s, dp[16] = { 1, };

int main() {
	std::cin >> N;
	if (N & 1) std::cout << 0;
	else {
		for (i = 1; i <= 15; ++i) {
			dp[i] = ((s += dp[i - 1]) << 1) + dp[i - 1];
			// dp[i] = dp[i - 1] * 3 + s * 2;
			// s += dp[i - 1];
			std::cout << dp[i] << '\n';
		}
		std::cout << dp[N >> 1];
	}
}