#include <iostream>

bool dp[51][1250][50]; // # of vertices, # of paths, # of degree
int N, S;

int main() { // O(N^4)
	std::cin >> N >> S;
	dp[3][1][1] = dp[3][1][2] = 1;
	for (int i = 3; i < N; ++i) {
		for (int j = 1; j <= i * (i - 1) / 2; ++j) {
			for (int k = 1; k < i; ++k) {
				if (dp[i][j][k])
					dp[i + 1][j + k][1] = dp[i + 1][j + k][k + 1] = 1;
			}
		}
	}
	std::cout << dp[N][S][1];
}