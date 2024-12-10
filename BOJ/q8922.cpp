#include <iostream>

int T, N, A[2][15];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		for (int i = 0; i < N; ++i) std::cin >> A[0][i];
		for (int i = 1; i < 1000; ++i) {
			for (int j = 0; j < N; ++j) {
				A[i & 1][j] = std::abs(A[~i & 1][j] - A[~i & 1][(j + 1) % N]);
			}
		}
		bool flag = 0;
		for (int i = 0; i < N; ++i) flag |= !!A[1][i];
		std::cout << (flag ? "LOOP\n" : "ZERO\n");
	}
}