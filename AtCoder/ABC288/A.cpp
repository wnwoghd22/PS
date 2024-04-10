#include <iostream>

int main() {
	int N, A, B;
	std::cin >> N;
	while (N--) {
		std::cin >> A >> B;
		std::cout << A + B << '\n';
	}
}