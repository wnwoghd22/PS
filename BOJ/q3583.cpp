#include <iostream>

int main() {
	int N;
	std::cin >> N;
	std::cout << 2 << ' ' << N << ' ' << N << '\n';
	for (int i = 0; i < N; ++i) {
		char c = i >= 26 ? i - 26 + 'a' : i + 'A';
		for (int j = 0; j < N; ++j) std::cout << c;
		std::cout << '\n';
	}
	std::cout << '\n';
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			char c = j >= 26 ? j - 26 + 'a' : j + 'A';
			std::cout << c;
		}
		std::cout << '\n';
	}

}