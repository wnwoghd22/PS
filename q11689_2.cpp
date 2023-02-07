#include <iostream>

typedef long long int ll;

ll phi(ll n) {
	ll result = n;
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

int main() {
	ll N;
	std::cin >> N;
	std::cout << phi(N);
}