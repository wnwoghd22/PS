#include <iostream>

int main() {
	int K;
	std::cin >> K;
	for (int i = 0; i < K; ++i) {
		std::cout << (char)('A' + i);
	}
}