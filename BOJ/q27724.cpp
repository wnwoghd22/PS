#include <iostream>
#include <cmath>

int main() {
	int N, M, K;
	std::cin >> N >> M >> K;
	int max = log2(N);
	int min = log2(K);
	std::cout << std::min(max, min + M);
}