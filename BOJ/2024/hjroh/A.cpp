#include <iostream>

int main() {
	int T, N;
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		std::cout << (N > 1 ? 3 : 1) << '\n';
	}
}