#include <iostream>
#include <cstring>

typedef long long ll;
const int LEN = 1'000'001;
const ll MOD = 1e9 + 7;

char S[LEN];
int T, dp[LEN], fail[LEN][21];
ll solve() {
	ll ret = 1;
	std::cin >> S;
	memset(dp, 0, sizeof dp);
	memset(fail, 0, sizeof fail);
	for (int i = 1, j = 0, k; S[i]; ++i) {
		while (j && S[j] ^ S[i]) j = fail[j - 1][0];
		if (S[j] == S[i]) {
			fail[i][0] = ++j;
			for (int p = 1; p < 21; ++p)
				fail[i][p] = fail[fail[i][p - 1] - 1][p - 1];
		}
		k = i;
		for (int p = 20; p >= 0; --p) {
			if (fail[k][p] >= i / 2)
				k = fail[k - 1][p];
		}
		ret = ret * (dp[fail[k][0]] + 1) % MOD;
		dp[i] = dp[fail[i][0]] + 1;

		for (int p = 0; p < 5; ++p) std::cout << fail[i][p] << ' '; std::cout << '\n';
	}
	for (int i = 0; S[i]; ++i) std::cout << dp[i] << ' ';
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';
}