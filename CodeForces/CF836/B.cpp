#include <iostream>

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int N;
		std::cin >> N;
		if (N & 1) {
			while (N--) std::cout << 1 << ' ';
		}
		else {
			int bit = 0;
			int sum = 0;

			// ???
		}
		std::cout << '\n';
	}
}