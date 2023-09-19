#include <iostream>

int main() {
	int T, N;
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		std::cout << "1A 1B";
		if (N == 2) {
			std::cout << "\n1A 2A";
			std::cout << "\n1A 2B";
		}
		if (N >= 3) {
			std::cout << "\n1A 2A";
			std::cout << "\n2A 3A";
			std::cout << "\n2B 3A";
			std::cout << "\n1A 3B";
		}
		for (int i = 4; i <= N; ++i) {
			std::cout << '\n' << (i - 2) << 'A' << ' ' << i << 'A';
			std::cout << '\n' << (i - 2) << 'B' << ' ' << i << 'B';
		}
		if (T > 1) std::cout << '\n';
	}
}