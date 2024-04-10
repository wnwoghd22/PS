#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 5001;
int N, dp[LEN];
char S[LEN];

int main() {
	std::cin >> N >> S;
	memset(dp, -1, sizeof dp);
	dp[0] = 0;
	dp[1] = dp[2] = 1;
	for (int i = 3; i <= N; ++i) {
		for (int j = 1, k = 0, e = 1; j <= 3; ++j, e *= 10) {
			if (S[i - j] == '0') continue;
			k += (S[i - j] - '0') * e;
			if (k > 641) break;
			if (!~dp[i - j]) continue;
			dp[i] = ~dp[i] ? std::min(dp[i], dp[i - j] + 1) : dp[i - j] + 1;
		}
	}
	std::cout << dp[N];
}
