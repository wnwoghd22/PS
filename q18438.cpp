#include <iostream>
#include <algorithm>
#include <string>

const int LEN = 7001;

std::string S, T;

int dp[2][LEN], *dp0, *dp1;

int main() {
	std::cin >> S >> T;
	for (int i = 0; i < S.length(); ++i) {
		dp0 = dp[~i & 1];
		dp1 = dp[i & 1];
		for (int j = 0; j < T.length(); ++j) {
			if (S[i] != T[j])
				dp1[j + 1] = std::max(dp1[j], dp0[j + 1]);
			else dp1[j + 1] = dp0[j] + 1;
		}
	}
	std::cout << dp1[T.length()];
}