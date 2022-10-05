#include <iostream>
#include <algorithm>
#include <cstring>

const int MAX = 100'001;
int dp[3][MAX];
int arr[2][MAX];
int N;

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		memset(arr, 0, sizeof arr);
		memset(dp, 0, sizeof dp);

		std::cin >> N;
		for (int i = 1; i <= N; ++i) std::cin >> arr[0][i];
		for (int i = 1; i <= N; ++i) std::cin >> arr[1][i];
		
		for (int i = 1; i <= N; ++i) {
			dp[0][i] = std::max(dp[1][i - 1], dp[2][i - 1]) + arr[1][i];
			dp[1][i] = std::max(dp[0][i - 1], dp[2][i - 1]) + arr[0][i];
			dp[2][i] = std::max({ dp[0][i - 1], dp[1][i - 1], dp[2][i - 1] });
		}
		
		std::cout << std::max({ dp[0][N], dp[1][N], dp[2][N] }) << '\n';
	}
}