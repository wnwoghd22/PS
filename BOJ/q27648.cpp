#include <iostream>

int main() {
	int N, M, K;
	std::cin >> N >> M >> K;
	if (K < N + M - 1) std::cout << "NO";
	else {
		std::cout << "YES\n";
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j)
				std::cout << i + j + 1 << ' ';
			std::cout << '\n';
		}
	}
}