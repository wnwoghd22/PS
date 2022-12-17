#include <iostream>

int N, M, result, bit[30];
char c;

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			std::cin >> c;
			if (c == 'o') bit[i] |= 1 << j;
		}
	}
	for (int i = 0; i < N; ++i) std::cout << bit[i] << '\n';

	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			if ((bit[i] | bit[j]) == (1 << M) - 1) result++;
		}
	}
	std::cout << result;
}