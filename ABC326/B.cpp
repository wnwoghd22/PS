#include <iostream>

int main() {
	int N;
	std::cin >> N;
	for (int i = N, A,d1, d2, d3; i <= 919; ++i) {
		A = i;
		d1 = A % 10; A /= 10;
		d2 = A % 10; A /= 10;
		d3 = A % 10; A /= 10;
		if (d2 * d3 == d1) {
			std::cout << i;
			return 0;
		}
	}
}