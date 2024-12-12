#include <iostream>

const int LEN = 101;
const int MAX = 20001;

int N, T, A[LEN], ans[LEN], dp[LEN][MAX];

int main() {
	std::cin >> N >> T;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	dp[2][A[1] - A[2] + 10000] = 1;
	for (int i = 3; i <= N; ++i) {
		for (int j = 0; j < MAX; ++j) {
			if (dp[i - 1][j]) {
				dp[i][j - A[i]] = 1;
				dp[i][j + A[i]] = 2;
			}
		}
	}
	for (int i = N, cur = T + 10000; i > 1; --i) {
		ans[i] = dp[i][cur];
		cur = ans[i] > 1 ? cur - A[i] : cur + A[i];
	}
	for (int i = 3; i <= N; ++i) std::cout << ans[i] << '\n';
	std::cout << 1;
}