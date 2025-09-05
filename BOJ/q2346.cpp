#include <iostream>

int N, M, A[1000];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];

	int i = 0;
	M = N;
	while (1) {
		std::cout << i + 1 << ' ';
		M--;
		if (!M) break;
		int dst = A[i];
		int dir = dst > 0 ? 1 : -1;
		// std::cout << dst << ' ' << dir << '\n';
		A[i] = 0;
		while (dst) {
			i = (i + N + dir) % N;
			if (A[i]) dst -= dir;
		}
	}
}