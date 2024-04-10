#include <iostream>

int main() {
	int T, l, r, x, a, b;
	std::cin >> T;
	while (T--) {
		std::cin >> l >> r >> x >> a >> b;
		if (a == b) {
			std::cout << "0\n";
			continue;
		}
		else if (abs(a - b) >= x) {
			std::cout << "1\n";
			continue;
		}
		else if (b < a) {
			if (l <= b - x || r >= a + x) {
				std::cout << "2\n";
				continue;
			}
			else {
				if (l <= a - x && r >= b + x) {
					std::cout << "3\n";
					continue;
				}
				else {
					std::cout << "-1\n";
					continue;
				}
			}
		}
		else if (b > a) {
			if (r >= b + x || l <= a - x) {
				std::cout << "2\n";
				continue;
			}
			else {
				if (r >= a + x && l <= b - x) {
					std::cout << "3\n";
					continue;
				}
				else {
					std::cout << "-1\n";
					continue;
				}
			}
		}
	}
}