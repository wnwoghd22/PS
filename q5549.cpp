#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int LEN = 1001;
int J[LEN][LEN], O[LEN][LEN], I[LEN][LEN];
int M, N, K, a, b, c, d;
char e;
struct S {
	int x;
};

int main() {
	S s;

	s->x = 1;
	freopen("input.txt", "r", stdin);
	std::cin >> M >> N >> K;
	for (int i = 1; i <= M; ++i) {
		for (int j = 1; j <= N; ++j) {
			std::cin >> e;
			J[i][j] = J[i - 1][j] + J[i][j - 1] - J[i - 1][j - 1] + (e == 'J');
			O[i][j] = O[i - 1][j] + O[i][j - 1] - O[i - 1][j - 1] + (e == 'O');
			I[i][j] = I[i - 1][j] + I[i][j - 1] - I[i - 1][j - 1] + (e == 'I');
		}
	}
	while (K--) {
		std::cin >> a >> b >> c >> d;
		std::cout << J[c][d] - J[a - 1][d] - J[c][b - 1] + J[a - 1][b - 1] << ' ';
		std::cout << O[c][d] - O[a - 1][d] - O[c][b - 1] + O[a - 1][b - 1] << ' ';
		std::cout << I[c][d] - I[a - 1][d] - I[c][b - 1] + I[a - 1][b - 1] << '\n';
	}
}
