#include <iostream>

int gcd(const int a, const int b) { return !b ? a : gcd(b, a % b); }

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int n, a, g, max = 0;
		std::cin >> n >> a; g = a; max = std::max(max, a);
		while (--n) std::cin >> a, max = std::max(max, a), g = gcd(g, a);
		std::cout << max / g << '\n';
	}
}