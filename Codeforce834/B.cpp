#include <iostream>

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int max = 0, sum = 0, result = false, m, s, b;
		std::cin >> m >> s;
		while (m--) {
			std::cin >> b;
			sum += b;
			max = std::max(max, b);
		}
		for (int i = max; i <= 300; ++i) {
			int total = i * (i + 1) / 2;
			if (sum + s == total) {
				result = true;
				break;
			}
		}
		if (result) std::cout << "YES\n";
		else std::cout << "NO\n";
	}
}