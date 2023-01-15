#include <iostream>

int main() {
	int a, b;
	std::cin >> a >> b;
	if (b == a * 2 || b == a * 2 + 1) std::cout << "Yes";
	else std::cout << "No";
}