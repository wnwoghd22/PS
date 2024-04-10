#include <iostream>

int main() {
	int N;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		if (i % 3 == 2) std::cout << 'X';
		else std::cout << 'O';
	}
}