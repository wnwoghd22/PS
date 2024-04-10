#include <iostream>

int main() {
	int N, L, A, C = 0;
	std::cin >> N >> L;
	while (N--) {
		std::cin >> A;
		if (A >= L) ++C;
	}
	std::cout << C;
}