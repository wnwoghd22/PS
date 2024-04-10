#include <iostream>
#include <cstring>

const int MOD = 1'000'000'007;

int dp[1001][10][10][11];
int N, A;

int f(int i, int j, int k, int d) {
	if (i == N) return !k;

	int& ref = dp[i][j][k][d];
	if (~ref) return ref;

	ref = 0;

	if (d < 10) {
		for (int e = j; e <= 9; ++e) {
			if (j + d ^ e) ref += f(i + 1, e, k - 1, 10);
			else ref += f(i + 1, e, k, d);
			ref %= MOD;
		}
	}
	else {
		for (int e = j; e <= 9; ++e) {
			ref += f(i + 1, e, k, e - j);
			ref %= MOD;
		}
	}
	return ref;
}

int main() {
	std::cin >> N >> A;
	if (A > 9) std::cout << 0;
	else {
		memset(dp, -1, sizeof dp);
		int result = 0;
		for (int i = 1; i <= 9; ++i) {
			result += f(1, i, A - 1, 10);
			result %= MOD;
		}
		std::cout << result;
	}
}