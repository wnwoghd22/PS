#include <iostream>

int main() {
	int L, R;
	std::cin >> L >> R;
	if (L ^ R) {
		std::cout << (L ? "Yes" : "No");
	} else std::cout << "Invalid";
}