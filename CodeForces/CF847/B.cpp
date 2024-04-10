#include <iostream>

void solve() {
	int n, s, r;
	std::cin >> n >> s >> r;
	int max = s - r;
	std::cout << max << ' ';
	int e = r / (n - 1);
	int remain = r - e * (n - 1);
	for (int i = 0; i < n - 1; ++i) {
		std::cout << e + (i < remain) << ' ';
	}
	std::cout << '\n';
}

int main() {
	int T;
	std::cin >> T;
	while (T--) solve();
}