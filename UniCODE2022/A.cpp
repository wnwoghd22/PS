#include <iostream>

int main() {
	int K, N = 0, S = 0, L = 0; char c, stack = 0;
	std::cin >> K;
	while (K--) {
		std::cin >> c;
		if (c == 'N') {
			if (stack == 'S') N = 1;
			else N++;
		}
		if (c == 'S') {
			if (stack == 'N') S = 1;
			else S++;
		}
		stack = c;
		L = std::max(L, std::min(N, S));
	}
	std::cout << L * 2;
}