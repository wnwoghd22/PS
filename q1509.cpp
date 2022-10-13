#include <iostream>
#include <cstring>

const int LEN = 2501;

char s[LEN];
int len;
bool p[LEN][LEN];
int dp[LEN];

int main() {
	std::cin >> s;
	len = strlen(s);

	for (int i = 0; i < len; ++i) p[i][i] = true;
	for (int i = 0; i < len - 1; ++i) if (s[i] == s[i + 1]) p[i][i + 1] = true; 
	for (int l = 3; l <= len; ++l) {
		for (int i = 0; i <= len - l; ++i) {
			int j = i + l - 1;
			if (s[i] == s[j] && p[i + 1][j - 1]) p[i][j] = true;
		}
	}

	/* for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j) {
			std::cout << p[i][j];
		}
		std::cout << '\n';
	} */

	memset(dp, -1, sizeof dp);
	dp[0] = 0; dp[1] = 1;
	for (int l = 2; l <= len; ++l) {
		for (int i = 1; i <= l; ++i) {
			if (p[i - 1][l - 1]) {
				if (!~dp[l] || dp[l] > dp[i - 1] + 1)
					dp[l] = dp[i - 1] + 1;
			}
		}
	}
	std::cout << dp[len];
}
