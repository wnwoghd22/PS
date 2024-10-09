#include <iostream>

int main() {
	int N, count = 0;
	std::cin >> N;
	while (N--) {
		char c; int D;
		std::cin >> c >> c >> D;
		if (D <= 90) count++;
	}
	std::cout << count;
}