#include <iostream>

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

int main() {
	int n, a0, a1, g, i, min, max;
	std::cin >> n >> a0 >> a1;
	min = a0 < a1 ? a0 : a1;
	max = a0 > a1 ? a0 : a1;
	g = max - min;
	for (i = 2; i < n; ++i) {
		a0 = a1;
		std::cin >> a1;
		if (a1 < min) min = a1;
		if (a1 > max) max = a1;
		g = gcd(g, abs(a1 - a0));
	}
	std::cout << (max - min) / g - n + 1;
}