#include <iostream>
#include <cmath>
#include <cassert>

typedef long long int ll;

ll F(ll n) {
	assert(n >= 0);
	if (n < 0) {
		std::cout << "invalid";
		return -1;
	}
	if (n == 0) return 0;
	if (n == 1) return 1;

	ll L = (ll)log2(n);
	ll sub = n - (1ll << L);

	return L * (1ll << (L - 1)) + sub + 1 + F(sub);
}

int main() {
	// ll A, B;
	// std::cin >> A >> B;
	// std::cout << F(B) - F(A - 1);

	for (ll i = 1000000000000000; i <= 10000000000000000; ++i) {
		std::cout << i << ": " << F(i) << '\n';
	}
}