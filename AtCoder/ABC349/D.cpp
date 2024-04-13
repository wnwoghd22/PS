#include <iostream>

typedef long long ll;

const int LEN = 100'001;

ll L, R;

int N;
ll l[LEN], r[LEN];

int main() {
	std::cin >> L >> R;

	ll cur = L, unit;

	if (!cur) {
		// std::cout << "l is 0\n";
		cur = 1;
		while (cur * 2 <= R) cur *= 2;
		l[N] = 0;
		r[N] = cur;
		++N;
	}
	else {
		while (1) {
			unit = cur & -cur;
			// std::cout << unit << '\n';
			if (cur + unit > R) break;
			l[N] = cur;
			r[N] = (cur += unit);
			++N;
		}
		// std::cout << cur << '\n';
	}
	unit = (cur & -cur) >> 1;
	// std::cout << cur << ' ' << unit << '\n';
	while (unit) {
		// std::cout << unit << '\n';
		if (R & unit) {
			l[N] = cur;
			r[N] = (cur += unit);
			++N;
		}
		unit >>= 1;
	}
	std::cout << N << '\n';
	for (int i = 0; i < N; ++i) std::cout << l[i] << ' ' << r[i] << '\n';
}