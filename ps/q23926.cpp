#include <iostream>

typedef long long ll;

// need to fix
ll f(ll x) {
	if (!x) return 0;
	ll ret = 0, sum = 0, l = 0, d[20], c[20];
	while (x) {
		d[l++] = x % 10;
		x /= 10;
	}
	int b = 0;
	ret = (d[l - 1] - 1) / 2;
	b = ~d[l - 1] & 1;
	for (int i = 1, a; i < l; ++i) {
		a = d[l - i - 1];
		ret = ret * 5 + 5 + a / 2;
	}
	return ret + 1;
}

int main() {
	int T;
	std::cin >> T;
	for (ll t = 1, l, r; t <= T; ++t) {
		std::cin >> l >> r;
		std::cout << "Case #" << t << ": " << f(r) - f(l - 1) << '\n';
	}
}