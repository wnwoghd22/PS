#include <iostream>

const int LEN = 1001;

int N, Q, S[4][2][LEN][LEN];
char A[LEN][LEN], s[3];


int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			std::cin >> A[i][j];
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j <= N; ++j) {
			S[A[i - 1][j - 1] - 'a' << 1 | A[i][j - 1] - 'a'][0][i][j] = 1;
			for (int k = 0; k < 4; ++k)
				S[k][0][i][j] += S[k][0][i - 1][j] + S[k][0][i][j - 1] - S[k][0][i - 1][j - 1];
		}
	}
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j < N; ++j) {
			S[A[i - 1][j - 1] - 'a' << 1 | A[i - 1][j] - 'a'][1][i][j] = 1;
			for (int k = 0; k < 4; ++k)
				S[k][1][i][j] += S[k][1][i - 1][j] + S[k][1][i][j - 1] - S[k][1][i - 1][j - 1];
		}
	}
	for (int k = 0; k < 4; ++k) {
		std::cout << (char)('a' + !!(k & 2)) << (char)('a' + !!(k & 1)) << '\n';
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j)
				std::cout << S[k][0][i][j] << ' ';
			std::cout << '\n';
		}
	}

	std::cin >> Q;
	for (int q = 0, i1, i2, j1, j2, k, l; q < Q; ++q) {
		std::cin >> i1 >> j1 >> i2 >> j2 >> s;
		k = s[0] - 'a' << 1 | s[1] - 'a';
		l = 0;
		if (i1 < i2) l += S[k][0][i2 - 1][j2] - S[k][0][i2 - 1][j1 - 1] - S[k][0][i1 - 1][j2] + S[k][0][i1 - 1][j1 - 1];
		if (j1 < j2) l += S[k][1][i2][j2 - 1] - S[k][1][i2][j1 - 1] - S[k][1][i1 - 1][j2 - 1] + S[k][1][i1 - 1][j1 - 1];
		std::cout << l << '\n';
	}
}