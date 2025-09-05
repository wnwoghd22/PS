#include <iostream>

int main() {
	(std::cout << std::fixed).precision(2);
	while (1) {
		long double n;
		long double a, s = 1;
		std::cin >> n;
		if (n < 1e-7) break;
		a = n;
		for (int i = 0; i < 4; ++i) {
			s += a;
			a *= n;
		}
		std::cout << s;
	}
}