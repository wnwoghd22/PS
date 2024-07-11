#include <iostream>

int main() {
	int N;
	std::cin >> N;
	if (N == 1) {
		std::cout << 1 << '\n';
		std::cout << "1 3" << '\n';
	}
	else if (N == 2) {
		std::cout << 3 << '\n';
		std::cout << "1 2" << '\n';
		std::cout << "1 3" << '\n';
		std::cout << "2 3" << '\n';
	}
	else if (N == 3) {
		std::cout << 5 << '\n';
		std::cout << "1 2" << '\n';
		std::cout << "1 2" << '\n';
		std::cout << "1 3" << '\n';
		std::cout << "2 3" << '\n';
		std::cout << "2 3" << '\n';
	}
	else std::cout << "Everything or Nothing";
}