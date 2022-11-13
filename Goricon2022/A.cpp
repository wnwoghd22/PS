#include <iostream>

int wK[100], wD[100], wA[100];

int main() {
	int N;
	std::cin >> N;
	while (N--) {
		int M;
		std::cin >> M;
		int K, D, A, result = 0;
		for (int i = 0; i < M; ++i) {
			std::cin >> wK[i] >> wD[i] >> wA[i];
		}
		std::cin >> K >> D >> A;
		for (int i = 0; i < M; ++i) {
			int w = wK[i] * K - wD[i] * D + wA[i] * A;
			if (w > 0) result += w;
		}
		std::cout << result << '\n';
	}
}