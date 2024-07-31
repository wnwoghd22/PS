#include <iostream>
#include <cstring>

typedef long long ll;
const int MOD = 1e9 + 7;
int N, K;
int dp[31][901];
int C[31][31];

ll f(int l, int k) {
	if (k > l * (l + 1) / 2) return 0;
	if (l < 0) return 0;
	if (l == 0) return 1;
	int& ref = dp[l][k];
	if (~ref) return ref;
	ref = 0;
	for (int i = 0, j = l - 1; j >= 0; ++i, --j) {
		for (int kk = 0; kk <= k - l; ++kk)
			ref = (ref + C[l - 1][i] * f(i, kk) % MOD * f(j, k - kk - l)) % MOD;
	}
	return ref;
}

int main() {
	std::cin >> N >> K;
	C[0][0] = 1;
	for (int i = 1; i <= N; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
	}

	memset(dp, -1, sizeof dp);
	std::cout << f(N, K);
}