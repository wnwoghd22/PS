#include <iostream>

int N;
void f(int n, int i) {
	if (n == 3) {
		std::cout << i + 1 << " to " << i - 2 << '\n';
		std::cout << i + 4 << " to " << i + 1 << '\n';
		std::cout << i + 2 << " to " << i - 4 << '\n';
		return;
	}
	if (n == 4) {
		std::cout << i + 5 << " to " << i - 2 << '\n'; 
		std::cout << i + 2 << " to " << i + 5 << '\n';
		std::cout << i - 1 << " to " << i + 2 << '\n';
		std::cout << i + 6 << " to " << i - 1 << '\n';
		return;
	}
	if (n == 5) {
		std::cout << i + 7 << " to " << i - 2 << '\n';
		std::cout << i + 2 << " to " << i + 7 << '\n';
		std::cout << i + 5 << " to " << i + 2 << '\n';
		std::cout << i - 1 << " to " << i + 5 << '\n';
		std::cout << i + 8 << " to " << i - 1 << '\n';
		return;
	}
	if (n == 6) {
		std::cout << i + 9 << " to " << i - 2 << '\n';
		std::cout << i + 6 << " to " << i + 9 << '\n';
		std::cout << i + 1 << " to " << i + 6 << '\n';
		std::cout << i + 5 << " to " << i + 1 << '\n';
		std::cout << i - 1 << " to " << i + 5 << '\n';
		std::cout << i + 10 << " to " << i - 1 << '\n';
		return;
	}
	if (n == 7) {
		std::cout << i + 11 << " to " << i - 2 << '\n';
		std::cout << i + 4 << " to " << i + 11 << '\n';
		std::cout << i + 7 << " to " << i + 4 << '\n';
		std::cout << i + 2 << " to " << i + 7 << '\n';
		std::cout << i + 8 << " to " << i + 2 << '\n';
		std::cout << i - 1 << " to " << i + 8 << '\n';
		std::cout << i + 12 << " to " << i - 1 << '\n';
		return;
	}
	std::cout << i + n * 2 - 3 << " to " << i - 2 << '\n';
	std::cout << i + 2 << " to " << i + n * 2 - 3 << '\n';
	f(n - 4, i + 4);
	std::cout << i - 1 << " to " << i + n * 2 - 6 << '\n';
	std::cout << i + (n - 1) * 2 << " to " << i - 1 << '\n';
}

int main() {
	std::cin >> N;
	f(N, 1);
}