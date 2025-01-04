#include <iostream>

typedef long long ll;

// need to fix
ll f(ll x) {
	ll ret = 0, l = 0, d[20], c[20];
	while (x) {
		d[l++] = x % 10;
		x /= 10;
	}
	for (int i = 0, b = 0, a; i < l; ++i) {
		a = d[l - i - 1];
		c[i] = b ? 4 : (a + 1) / 2;
		if (~a & (i & 1)) b = 1;
	}
	std::cout << "C: ";
	for (int i = 0; i < l; ++i) std::cout << c[i] << ' '; std::cout << '\n';
	
	std::cout << "D: ";
	for (int i = 0; i < l; ++i) std::cout << d[i] << ' '; std::cout << '\n';

	for (int i = 0; i < l; ++i) ret = ret * 5 + c[i];
	return ret;
}

int main() {
	int T;
	ll l, r;
	std::cin >> T;
	while (T--) {
		std::cin >> l >> r;
		std::cout << f(r) - f(l - 1) << '\n';
	}
}