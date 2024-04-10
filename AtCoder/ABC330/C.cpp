#include <iostream>
#include <algorithm>

typedef long long ll;

int main() {
	ll D, X, Y, answer;
	std::cin >> D;
	answer = 1e12;
	for (X = 1; X * X <= D; ++X) {
		ll l = 1, r = 1e6, m;
		Y = 0;
		while (l <= r) {
			m = l + r >> 1;
			if (X * X + m * m <= D) {
				Y = std::max(Y, m);
				l = m + 1;
			}
			else r = m - 1;
		}
		answer = std::min(answer, std::abs(X * X + Y * Y - D));
		answer = std::min(answer, std::abs(X * X + (Y + 1) * (Y + 1) - D));
	}
	std::cout << answer;
}