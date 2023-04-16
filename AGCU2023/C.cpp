#include <iostream>
int main() {
	long long N;
	std::cin >> N;
	if (!N) std::cout << 0;
	else {
		long long k = 1, i = 1;
		while (k < N) k <<= 1, ++i;
		std::cout << i;
	}
}