#include <iostream>

int main() {
	int N;
	std::cin >> N;
	if (N == 1) std::cout << 0;
	else std::cout << N * N - N * N / 2;
}