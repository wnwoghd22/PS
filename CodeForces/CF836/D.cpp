#include <iostream>
#include <cmath>

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int n;
		std::cin >> n;
		if (n & 1) {
			for (int i = n - n / 2 + 1; i <= n; ++i) std::cout << i << ' ';
			for (int i = 0; i < n - n / 2; ++i) std::cout << n + i + 3 << ' ';
		}
		else {
			for (int i = n / 2; i < n; ++i) std::cout << i << ' ';
			for (int i = 1; i <= n / 2; ++i) std::cout << i + n << ' ';
		}
		std::cout << '\n';
	}
}