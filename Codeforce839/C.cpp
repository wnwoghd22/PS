#include <iostream>

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int N, K;
		std::cin >> K >> N;
		int a = 1, ch = 1;
		for (int i = 0; i < K; ++i) {
			std::cout << (i == K - 1 ? N : a) << ' ';
			if (N - (a + ch) > K - i - 1) a += ch++;
			else a += 1;
		}
		std::cout << '\n';
	}
}