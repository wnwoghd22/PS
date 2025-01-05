#include <iostream>

typedef long long ll;

ll f(ll x) {
	if (!x) return 0;
	ll ret = 0, sum = 0, l = 0, d[20];
	while (x) {
		d[l++] = x % 10;
		x /= 10;
	}
	ret = d[l - 1] / 2;
	int b = ~d[l - 1] & 1;
	for (int i = 1, a; i < l; ++i) {
		a = d[l - i - 1];
		ret = ret * 5 + 5;
		if (!b) {
			if (i & 1) { // even
				b = a & 1;
				ret += a / 2 + b;
			}
			else { // odd
				ret += a / 2;
				b = ~a & 1;
			}
		}	
	}
	return ret + !b;
}

int main() {
	int T;
	std::cin >> T;
	for (ll t = 1, l, r; t <= T; ++t) {
		std::cin >> l >> r;
		std::cout << "Case #" << t << ": " << f(r) - f(l - 1) << '\n';
	}
}