#include <iostream>
#include <cstring>

const int MOD = 1'000'000'000;
int dp[10][101][1 << 10];
int N;

int F(int d, int n, int bit) {
	if (n == N) return bit == 1023;
	int& ref = dp[d][n][bit];
	if (~ref) return ref;

	ref = 0;
	if (d > 0) ref += F(d - 1, n + 1, bit | 1 << d - 1);
	if (d < 9) ref += F(d + 1, n + 1, bit | 1 << d + 1);
	return ref %= MOD;
}

int main() {
	memset(dp, -1, sizeof dp);
	std::cin >> N;
	int result = 0;
	for (int i = 1; i < 10; ++i) {
		result += F(i, 1, 1 << i);
		result %= MOD;
	}
	std::cout << result;
}