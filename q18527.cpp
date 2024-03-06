#include <iostream>

typedef long long ll;
const ll MOD = 998'244'353;
const int LEN = 1e5;
int n, t, x[LEN];

ll pow(ll a, ll b) {
	ll ret = 1;
	while (b) {
		if (b & 1) ret = ret * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return ret;
}

int main() {
	std::cin >> n >> t;

	ll p = 1, s = t + n + 1, d;
	for (int i = 0; i < n; ++i) std::cin >> x[i], s -= x[i]; d = s;
	for (int i = 0; i < n; ++i) {
		p = p * s % MOD;
		s += x[i] - 1;
	}
	// std::cout << p << '\n';
	p = p * (d - n) % MOD * pow(d, MOD - 2) % MOD;
	std::cout << p << '\n';
}