#include <iostream>

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int n, a, b;
		std::cin >> n >> a >> b;
		if (a == n && b == n) {
			std::cout << "YES\n";
		}
		else {
			if (n - (a + b) >= 2) std::cout << "YES\n";
			else std::cout << "NO\n";
		}
	}
}