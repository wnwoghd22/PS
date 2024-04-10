#include <iostream>

int main() {
	int cur = 1, next, mod;
	std::cout << cur << std::endl;
	do {
		std::cin >> next;
		mod = next % 3;
		cur = next % 3 ? next + (next % 3 ^ 3) : next + 1;
		std::cout << cur << std::endl;
	} while (cur < 99);
}