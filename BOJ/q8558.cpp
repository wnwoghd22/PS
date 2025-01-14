#include <iostream>

int main() {
	int N;
	std::cin >> N;
	N = N > 4 ? 5 : N;
	std::cout << "112640"[N];
}