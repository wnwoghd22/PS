#include <iostream>

const int LEN = 20;
int N, M, A[LEN], B[LEN], C[LEN], ans[LEN];
int f(int b) { return (b << 1 ^ b ^ b >> 1) & (1 << N) - 1; }

int main() {
	std::cin >> M >> N;
	for (int i = 0; i < M; ++i) {
		for (int j = N - 1, b; j >= 0; --j) {
			std::cin >> b;
			A[i] |= b << j;
		}
	}
	int ret = 300;
	for (C[0] = 0; C[0] < (1 << N); ++C[0]) {
		int cnt = 0;
		for (int b = C[0]; b > 0; b -= b & -b) cnt++;
		B[0] = A[0] ^ f(C[0]);
		B[1] = A[1] ^ C[0];
		for (int i = 1; i < M; ++i) {
			C[i] = B[i - 1];
			for (int b = C[i]; b > 0; b -= b & -b) cnt++;
			B[i] ^= f(C[i]);
			B[i + 1] = A[i + 1] ^ C[i];
		}
		if (!B[M - 1] && cnt < ret) {
			ret = cnt;
			for (int i = 0; i < M; ++i) ans[i] = C[i];
		}
	}
	if (ret < 300) {
		for (int i = 0; i < M; ++i) {
			for (int j = N - 1; j >= 0; --j)
				std::cout << (ans[i] >> j & 1) << ' ';
			std::cout << '\n';
		}
	}
	else std::cout << "IMPOSSIBLE";
}