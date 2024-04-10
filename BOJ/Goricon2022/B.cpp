#include <iostream>

int A[3000][3000];
int* p[3000];

int main() {
	int N, M, nQ, q, i, j, k;
	std::cin >> N >> M >> nQ;

	for (i = 0; i < N; ++i) {
		p[i] = A[i];
		for (j = 0; j < M; ++j) std::cin >> p[i][j];
	}

	while (nQ--) {
		std::cin >> q;
		if (q) {
			std::cin >> i >> j;
			int* temp = p[i];
			p[i] = p[j];
			p[j] = temp;
		}
		else {
			std::cin >> i >> j >> k;
			p[i][j] = k;
		}
	}

	for (i = 0; i < N; ++i) {
		for (j = 0; j < M; ++j)
			std::cout << p[i][j] << ' ';
		std::cout << '\n';
	}
}