#include <iostream>

int main() {
	int a, b, c;
	std::cin >> a >> b >> c;
	std::cout << a + b - c << '\n';
	int e = 1;
	while (e <= b) e *= 10;
	std::cout << a * e + b - c;
}