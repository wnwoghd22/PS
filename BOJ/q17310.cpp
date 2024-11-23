#include <iostream>
#include <cstring>

typedef long long ll;
const int LEN = 1'000'001;
const ll MOD = 1e9 + 7;

char S[LEN];
int T, dp[LEN], fail[LEN], p[LEN][21];
ll solve() {
	ll ret = 1;
	std::cin >> S;
	memset(dp, 0, sizeof dp);
	memset(fail, 0, sizeof fail);
	memset(p, 0, sizeof p);
	for (int i = 1, j = 0, k; S[i]; ++i) {
		while (j && S[j] ^ S[i]) j = fail[j - 1];
		if (S[j] == S[i]) {
			p[i][0] = j;
			fail[i] = ++j;
			for (int d = 1; d < 21; ++d)
				p[i][d] = p[p[i][d - 1]][d - 1];
		}
		k = i;
		for (int d = 20; d >= 0; --d) {
			if (p[k][d] + 1 > (i + 1) / 2)
				k = p[k][d];
		}
		if (S[i] == S[p[k][0]]) ret = ret * (dp[p[k][0]] + 2) % MOD;
		if (S[i] == S[p[i][0]]) dp[i] = dp[p[i][0]] + 1;
		std::cout << i << ' ' << p[i][0] << ' '  << S[i] << ' ' << S[p[i][0]] << ' ' << fail[i] << ' ' << k << '\n';
	}
	for (int i = 0; S[i]; ++i) std::cout << dp[i] << ' ';
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';
}