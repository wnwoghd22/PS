#include <iostream>

typedef long long int ll;

int main() {
	ll T, R, C;
	std::cin >> T;
	while (T--) {
		ll black = 0, white = 0;
		std::cin >> R >> C;
		ll tR = R, tC = C;

		ll step = std::min(R, C);
		ll r = R - step + 1, c = C - step + 1;
		ll base = r * c;
		ll square = base * (step + 1) * step / 2 + (step - 1) * step * (step + 1) / 3;

		black = square * 2 - (R + C + r + c) * step / 2;
		white = black + step;

		std::cout << white << ' ' << black << '\n';
	}
}