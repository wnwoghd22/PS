#include <iostream>

typedef long double ld;
const int LEN = 1002;

int P, N;
ld l, r, m, dp[2][LEN];

ld solve() {
	std::cin >> N >> l >> r;
	m = 1 - l - r;
	dp[0][0] = 1;
	for (int i = 1; i <= N; ++i) dp[0][i] = dp[1][i] = 0;
	for (int i = 1; i <= N; ++i) {
		dp[i & 1][0] = dp[~i & 1][1] * l + dp[~i & 1][0] * (l + m);
		for (int j = 1; j <= i; ++j) {
			dp[i & 1][j] = dp[~i & 1][j + 1] * l + dp[~i & 1][j] * m + dp[~i & 1][j - 1] * r;
		}
	}
	ld ret = 0;
	for (int i = 0; i <= N; ++i) ret += i * dp[N & 1][i];
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cout << std::fixed;
	std::cout.precision(4);
	std::cin >> P;
	while (P--) std::cout << solve() << '\n';
}