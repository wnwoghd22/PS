#include <iostream>

void solve() {
	int n;
	std::cin >> n;
	if (n & 1) {
		std::cout << "-1\n";
		return;
	}
	for (int i = 1; i < 32; ++i) {
		if ((n & (1 << i)) && (n & (1 << (i - 1)))) {
			std::cout << "-1\n";
			return;
		}
	}
	int a = 0, b = 0;

	for (int i = 1; i < 32; ++i) {
		if (n & (1 << i)) {
			a |= 3 << (i - 1);
			b |= 1 << (i - 1);
		}
	}
	std::cout << a << ' ' << b << '\n';
}

int main() {
	int T;
	std::cin >> T;
	while (T--) solve();
}