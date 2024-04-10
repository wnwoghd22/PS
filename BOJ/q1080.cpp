#include <iostream>

bool A[50][50], B[50][50];
char S[51];
void flip(int x, int y) {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			A[x + i][y + j] ^= 1;
}
int N, M, K;

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		std::cin >> S;
		for (int j = 0; j < M; ++j) A[i][j] = S[j] == '1';
	}
	for (int i = 0; i < N; ++i) {
		std::cin >> S;
		for (int j = 0; j < M; ++j) B[i][j] = S[j] == '1';
	}
	for (int i = 0; i < N - 2; ++i) {
		for (int j = 0; j < M - 2; ++j) {
			if (A[i][j] != B[i][j])
				flip(i, j), ++K;
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (A[i][j] != B[i][j]) {
				std::cout << -1;
				return 0;
			}
		}
	}
	std::cout << K;
}