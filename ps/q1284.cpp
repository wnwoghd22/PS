#include <iostream>

int main() {
	int N;
	while (1) {
		std::cin >> N;
		if (!N) break;
		int ret = 1;
		while (N) {
			int d = N % 10;
			N /= 10;
			ret += (d == 0 ? 4 : d == 1 ? 2 : 3) + 1;
		}
		std::cout << ret << '\n';
	}
}