#include <iostream>

const int LEN = 100'001;
int N, M, A[LEN], S[LEN], dp[LEN], result;

int main() {
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		S[i] = S[i - 1] + A[i];
	}
	dp[M] = S[M];
	for (int i = M + 1; i <= N; ++i) {
		dp[i] = std::max(dp[i - 1] + A[i], S[i] - S[i - M]);
		result = std::max(result, dp[i]);
	}
	std::cout << result;
}