#include <iostream>
#include <algorithm>

const int LEN = 10'001;
const int INF = 1e9;
int dp[LEN][10];
char s[LEN], t[LEN];
int N;

int F() {
	for (int i = 1; i <= N; ++i)
		for (int j = 0; j < 10; ++j)
			dp[i][j] = INF;
	for (int i = 0; i < 10; ++i) dp[0][i] = i;

	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j < 10; ++j) {
			int left = (t[i - 1] - s[i - 1] - j + 20) % 10;
			int right = 10 - left;

			dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + right);
			dp[i][(j + left) % 10] = std::min(dp[i][(j + left) % 10], dp[i - 1][j] + left);
		}
	}

	for (int j = 0; j < 10; ++j) {
		for (int i = 1; i <= N; ++i) {
			std::cout << dp[i][j] << ' ';
		}
		std::cout << '\n';
	}

	return *std::min_element(dp[N], dp[N] + 10);
}

int main() {
	std::cin >> N >> s >> t;
	std::cout << F();
}