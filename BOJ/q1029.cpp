#include <iostream>
#include <cstring>

int dp[15][10][1 << 15]; // num, cost, bit
std::string s[15];
int N;

int f(int i, int c, int bit) {
	if (bit == (1 << N) - 1) return 0;
	int& ref = dp[i][c][bit];
	if (~ref) return ref;
	ref = 0;
	for (int j = 1; j < N; ++j) {
		if (bit & (1 << j)) continue;
		if (s[i][j] - '0' >= c) ref = std::max(ref, f(j, s[i][j] - '0', bit | (1 << j)) + 1);
	}
	return ref;
}

int main() {
	memset(dp, -1, sizeof dp);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> s[i];
	std::cout << f(0, 0, 1) + 1;
}