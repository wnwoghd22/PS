#include <iostream>

int gcd(const int a, const int b) { return !b ? a : gcd(b, a % b); }

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int x, y;
		std::cin >> x >> y;
		int k, d, a;
		std::cin >> k >> a; d = a;
		while (--k) std::cin >> a, d = gcd(d, a);
		x %= d, y %= d;
		if (!x && !y) std::cout << "Ta-da\n";
		else std::cout << "Gave up\n";
	}
}