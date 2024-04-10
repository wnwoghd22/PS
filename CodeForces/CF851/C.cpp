#include <iostream>

int N;

void solve() {
	std::cin >> N;
	if (N & 1) {
		std::cout << "Yes\n";
		int mid = 2 * N + 1;
		int sum = mid - N / 2;
		for (int i = 0; i < N / 2 + 1; ++i) {
			int a = 2 * i + 1;
			std::cout << a << ' ' << sum - a << '\n';
			++sum;
		}
		for (int i = 1; i <= N / 2; ++i) {
			int a = 2 * i;
			std::cout << a << ' ' << sum - a << '\n';
			++sum;
		}
	}
	else std::cout << "No\n";
}

int main() {
	int T;
	std::cin >> T;
	while (T--) solve();
}