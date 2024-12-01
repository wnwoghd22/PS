#include <iostream>

int main() {
	int a, b, c, d, e, f, x, y, num, den;
	std::cin >> a >> b >> c >> d >> e >> f;
	den = (b * d - a * e); num = (c * d - a * f);
	y = den ? num / den : 0;
	x = (c - b * y) / a;
	std::cout << x << ' ' << y;
}