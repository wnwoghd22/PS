#include <iostream>

int main() {
	int max = (1 << 10) - 1;
	int A, B, C;
	std::cin >> A >> B;
	C = (A ^ B) & max;
	std::cout << C;
}