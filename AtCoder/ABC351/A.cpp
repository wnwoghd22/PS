#include <iostream>

int main() {
	int A = 0, B = 0;
	for (int i = 0, a; i < 9; ++i) {
		std::cin >> a;
		A += a;
	}
	for (int i = 0, b; i < 8; ++i) {
		std::cin >> b;
		B += b;
	}
	std::cout << (A - B + 1);
}