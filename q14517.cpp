#include <iostream>
#include <cstring>

const int MOD = 10'007;
int dp[1000][1000];
char s[1001];
int len;

int main() {
	std::cin >> s;
	len = strlen(s);
	for (int i = 0; i < len; ++i) dp[i][i] = 1;
	for (int l = 1; l < len; ++l)
		for (int i = 0, j = l; j < len; ++i, ++j)
			dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + (s[i] == s[j]) * (dp[i + 1][j - 1] + 1)) % MOD;

	/*for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j)
			std::cout << dp[i][j] << ' ';
		std::cout << '\n';
	} */

	std::cout << dp[0][len - 1];
}