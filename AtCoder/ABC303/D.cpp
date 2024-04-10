#include <iostream>

const int LEN = 3e5 + 1;
typedef long long ll;
ll X, Y, Z, i;
char S[LEN];
ll dp[LEN][2]; // 0: OFF, 1: ON

int main() {
	std::cin >> X >> Y >> Z >> S;
	if (S[0] == 'A') {
		dp[0][0] = Y;
		dp[0][1] = Z + X;
	}
	else if (S[0] == 'a') {
		dp[0][0] = X;
		dp[0][1] = Z + Y;
	}
	for (i = 1; S[i]; ++i) {
		if (S[i] == 'A') {
			dp[i][0] = std::min(dp[i - 1][0] + Y, dp[i - 1][1] + Z + Y);
			dp[i][1] = std::min(dp[i - 1][1] + X, dp[i - 1][0] + Z + X);
		}
		else if (S[i] == 'a') {
			dp[i][0] = std::min(dp[i - 1][0] + X, dp[i - 1][1] + Z + X);
			dp[i][1] = std::min(dp[i - 1][1] + Y, dp[i - 1][0] + Z + Y);
		}
	}
	std::cout << std::min(dp[i - 1][0], dp[i - 1][1]);
}