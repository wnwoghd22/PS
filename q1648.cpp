#include <iostream>
#include <cstring>

const int MOD = 9901;
int dp[14 * 14 + 1][1 << 14];
int N, M;

int F(int x, int bit) {
	if (x == N * M && !bit) return 1;
	if (x >= N * M) return 0;
	int& ref = dp[x][bit];
	if (~ref) return ref;

	if (bit & 1) ref = F(x + 1, bit >> 1);
	else {
		ref = F(x + 1, bit >> 1 | 1 << M - 1);
		if (~(x % M - M) && ~bit & 2) ref += F(x + 2, bit >> 2);
	}
	return ref %= MOD;
}

int main() {
	std::cin >> N >> M;
	memset(dp, -1, sizeof dp);
	std::cout << F(0, 0);
}