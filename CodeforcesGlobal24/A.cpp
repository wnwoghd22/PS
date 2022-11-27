#include <iostream>

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int n, a;
		std::cin >> n;
		for (int i = 0; i < n; ++i) std::cin >> a;
		std::cout << 1 << ' ' << n << '\n';
	}
}