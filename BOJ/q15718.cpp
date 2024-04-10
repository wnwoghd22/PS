#include <iostream>

const int MOD = 100'007, MOD1 = 97, MOD2 = 1031;
const int INV1 = 659, INV2 = 35;
int C1[MOD1][MOD1], C2[MOD2][MOD2];
int T, N, M;

int solve(int N, int M) {
	if (!N && M == 1) return 1;
	if (!N || M == 1) return 0;

	int result1 = 1, n = N - 1, m = M - 2;
	while (n || m) {
		result1 = result1 * C1[n % MOD1][m % MOD1] % MOD1;
		n /= MOD1, m /= MOD1;
	}
	int result2 = 1; n = N - 1, m = M - 2;
	while (n || m) {
		result2 = result2 * C2[n % MOD2][m % MOD2] % MOD2;
		n /= MOD2, m /= MOD2;
	}

	int result = (MOD2 * INV2 * result1 + MOD1 * INV1 * result2) % MOD;
	return result;
}

int main() {
	for (int i = 0; i < MOD1; ++i) {
		C1[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C1[i][j] = (C1[i - 1][j - 1] + C1[i - 1][j]) % MOD1;
	}
	for (int i = 0; i < MOD2; ++i) {
		C2[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C2[i][j] = (C2[i - 1][j - 1] + C2[i - 1][j]) % MOD2;
	}

	std::cin >> T;
	while (T--) {
		std::cin >> N >> M;
		std::cout << solve(N, M) << '\n';
	}
}