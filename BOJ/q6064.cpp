#include <iostream>

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int M, N, x, y;
		std::cin >> M >> N >> x >> y;

		y %= N;

		int limit = M * N;
		int year = x;
		while (true) {
			if (year % N == y) break;
			year += M;
			if (year > limit) {
				year = -1;
				break;
			}
		}
		std::cout << year << '\n';
	}
}