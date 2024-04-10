#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

const int LEN = 3e6+1;
int N, P, fibo[32] = { 1, 1 };
int dp[LEN] = { 0, 1, 2, 3, };
bool mex[16];

int main() {
	freopen("input.txt", "r", stdin);
	for (int i = 2; i < 32; ++i)
		fibo[i] = fibo[i - 1] + fibo[i - 2];
	// for (int i = 0; i < 32; ++i) std::cout << fibo[i] << '\n';

	for (int i = 4; i < LEN; ++i) {
		memset(mex, 0, sizeof mex);
		for (int j = 1; j < 32; ++j) {
			if (fibo[j] > i) break;
			mex[dp[i - fibo[j]]] = 1;
		}
		for (int k = 0; k < 16; ++k) {
			if (!mex[k]) {
				dp[i] = k;
				break;
			}
		}
	}
	// for (int i = 0; i < 1000; ++i) std::cout << dp[i] << ' ';
	while (std::cin >> N) {
		int result = 0;
		while (N--) {
			std::cin >> P;
			result ^= dp[P];
		}
		std::cout << (result ? "koosaga" : "cubelover") << '\n';
	}
}