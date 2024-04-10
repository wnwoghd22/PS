#include <iostream>

typedef long double ld;

int main() {
	int N;
	ld result = 0;
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		result += (ld)N / i;
	}
	std::cout << std::fixed;
	std::cout.precision(10);
	std::cout << result;
}