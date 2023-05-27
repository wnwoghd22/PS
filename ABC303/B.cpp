#include <iostream>

int N, M, A, cnt, mat[51][51];

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int a0, a1;
		std::cin >> a0;
		for (int j = 1; j < N; ++j) {
			std::cin >> a1;
			mat[a0][a1] = 1;
			mat[a1][a0] = 1;
			a0 = a1;
		}
	}
	cnt = N * (N - 1);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j)
			cnt -= mat[i][j];
	}
	std::cout << (cnt >> 1);
}