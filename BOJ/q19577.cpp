#include <iostream>

typedef long long ll;
const int MAX = 1e9 + 7;

ll phi(ll n) {
	ll result = n;
	ll k = n;
	for (ll i = 2; i * i <= n; ++i) {
		ll p = 0;
		while (!(n % i)) {
			n /= i;
			++p;
		}
		if (p) {
			result /= i;
			result *= (i - 1);
		}
	}
	if (n > 1) {
		result /= n;
		result *= (n - 1);
	}
	return result;
}

int N;

int main() {
	std::cin >> N;
	ll ret = MAX;
	for (ll x = 1; x * x <= N; ++x) {
		if (N % x == 0) {
			ll y = N / x;
			if (x * phi(x) == N) ret = std::min(ret, x);
			if (y * phi(y) == N) ret = std::min(ret, y);
		}
	}
	std::cout << (ret == MAX ? -1 : ret);
}