#include <iostream>
#define ABS(x) ((x) >= 0 ? (x) : -(x))

typedef long long ll;
ll ret, dp[1 << 16][16];

int N, K, H[16];

int main() {
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i)
		std::cin >> H[i];
	for (int b = 1; b < (1 << N); ++b) {
		for (int i = 0; i < N; ++i) {
			if (b == 1 << i) { dp[b][i] = 1; continue; }
			if (~b & (1 << i)) continue;
			for (int j = 0; j < N; ++j) {
				if ((b & 1 << j) && ABS(H[i] - H[j]) > K)
					dp[b][i] += dp[b ^ (1 << i)][j];
			}
		}
	}
	for (int i = 0; i < N; ++i) ret += dp[(1 << N) - 1][i];
	std::cout << ret;
}