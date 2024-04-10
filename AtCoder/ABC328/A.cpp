#include <iostream>

int N, X, A, S;

int main() {
	std::cin >> N >> X;
	while (N--) {
		std::cin >> A;
		if (A <= X) S += A;
	}
	std::cout << S;
}