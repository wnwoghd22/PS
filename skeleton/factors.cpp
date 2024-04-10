#include <iostream>

typedef long long ll;
const ll MOD = 1e9 + 7;

ll naive(ll n) {
	ll result = 0;
	for (ll i = 1; i <= n; ++i)
		result = (result + n / i) % MOD;
	return result;
}

ll f(ll n) {
	ll result = 0;
	for (ll i = 1, j; i <= n; i = j) {
		ll cur = n / i;
		j = n / cur + 1;
		result = (result + cur * (j - i) % MOD) % MOD;
	}
	return result;
}

int main() {
	std::cout << naive(10) << ' ' << f(10) << '\n';
	std::cout << naive(100) << ' ' << f(100) << '\n';
	std::cout << f(123456789012) << '\n';

}