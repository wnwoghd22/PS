#include <iostream>

int S[2000];

int main() {
	int N, M, T;

	std::cin >> N >> M;

	for (int i = 0; i < N; ++i) std::cin >> S[i];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N + M; ++j) {
			std::cin >> T;
			S[i] -= T;
			S[j] += T;
		}
	}
	for (int i = 0; i < N + M; ++i) std::cout << S[i] << ' ';
}