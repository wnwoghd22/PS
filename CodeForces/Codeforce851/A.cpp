#include <iostream>

int N, two, arr[1000];

int solve() {
	two = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> arr[i];
		if (arr[i] == 2) ++two;
	}
	if (!two) {
		std::cout << 1 << '\n';
		return 0;
	}
	if (two & 1) {
		std::cout << -1 << '\n';
		return 0;
	}
	for (int i = 0, half = 0; i < N; ++i) {
		if (arr[i] == 2) {
			++half;
		}
		if (half == two / 2) {
			std::cout << i + 1 << '\n';
			return 0;
		}
	}
}

int main() {
	int T;
	std::cin >> T;
	while (T--) solve();
}