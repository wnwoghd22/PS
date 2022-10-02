#include <iostream>
#include <cmath>

typedef long long int ll;

ll F(ll n) {
	for (ll i = 0, k = 1; i <= log10(n); ++i, k *= 10) {
		ll sup = n / k, sub = n % k, digit = sup % 10; sup /= 10;
		if (digit == 1) return sup * k + sub;
	}

	return n - 1;
}

int main() {
	ll N, count = 0;
	std::cin >> N;
	while (N != 0) {
		N = F(N);
		count++;
	}
	std::cout << count;
}