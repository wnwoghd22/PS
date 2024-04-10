#include <iostream>

const int LEN = 1'000'001;
const int MOD = 1e9 + 7;

int N, dp[LEN][9]; // R: 0, P: 3, S: 6 / Tie: 0, Win: 1, Lose: 2

char A, S[LEN];

int main() {
	std::cin >> A >> S;
	N = strlen(S);

	if (A == 'R') dp[0][0] = 1;
	if (A == 'P') dp[0][3] = 1;
	if (A == 'S') dp[0][6] = 1;

	for (int i = 1; i <= N; ++i) {
		if (S[i - 1] == 'R') {
			dp[i][0] = (dp[i][0] + dp[i - 1][0]) % MOD; // tie - tie
			dp[i][0] = (dp[i][0] + dp[i - 1][2]) % MOD; // lose - tie

			dp[i][1] = (dp[i][1] + dp[i - 1][3]) % MOD; // tie - win
			dp[i][1] = (dp[i][1] + dp[i - 1][4]) % MOD; // win - win
			dp[i][1] = (dp[i][1] + dp[i - 1][5]) % MOD; // lose - win

			dp[i][2] = (dp[i][2] + dp[i - 1][6]) % MOD; // tie - lose
			dp[i][2] = (dp[i][2] + dp[i - 1][7]) % MOD; // win - lose
			dp[i][2] = (dp[i][2] + dp[i - 1][8]) % MOD; // lose - lose
		}
		if (S[i - 1] == 'P') {
			dp[i][3] = (dp[i][3] + dp[i - 1][3]) % MOD; // tie - tie
			dp[i][3] = (dp[i][3] + dp[i - 1][5]) % MOD; // lose - tie

			dp[i][4] = (dp[i][4] + dp[i - 1][6]) % MOD; // tie - win
			dp[i][4] = (dp[i][4] + dp[i - 1][7]) % MOD; // win - win
			dp[i][4] = (dp[i][4] + dp[i - 1][8]) % MOD; // lose - win

			dp[i][5] = (dp[i][5] + dp[i - 1][0]) % MOD; // tie - lose
			dp[i][5] = (dp[i][5] + dp[i - 1][1]) % MOD; // win - lose
			dp[i][5] = (dp[i][5] + dp[i - 1][2]) % MOD; // lose - lose
		}
		if (S[i - 1] == 'S') {
			dp[i][6] = (dp[i][6] + dp[i - 1][6]) % MOD; // tie - tie
			dp[i][6] = (dp[i][6] + dp[i - 1][8]) % MOD; // lose - tie

			dp[i][7] = (dp[i][7] + dp[i - 1][0]) % MOD; // tie - win
			dp[i][7] = (dp[i][7] + dp[i - 1][1]) % MOD; // win - win
			dp[i][7] = (dp[i][7] + dp[i - 1][2]) % MOD; // lose - win

			dp[i][8] = (dp[i][8] + dp[i - 1][3]) % MOD; // tie - lose
			dp[i][8] = (dp[i][8] + dp[i - 1][4]) % MOD; // win - lose
			dp[i][8] = (dp[i][8] + dp[i - 1][5]) % MOD; // lose - lose
		}
		for (int j = 0; j < 9; ++j) {
			dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
			// std::cout << dp[i][j] << ' ';
		}
		// std::cout << '\n';
	}
	int ret = 0;
	for (int i = 0; i < 9; ++i) ret = (ret + dp[N][i]) % MOD;
	std::cout << (ret - 1 + MOD) % MOD;
}