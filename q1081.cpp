#include <iostream>
#include <cmath>

typedef long long int ll;
ll result, cnt[10];

ll F(int d, ll n) {
	if (n < 0) return 0;
	ll result = 0;

	for (ll i = 0, k = 1; i <= log10(n); ++i, k *= 10) {
		ll sup = n / k, sub = n % k, digit = sup % 10; sup /= 10;

		if (d) result += sup * k + (digit > d ? k : digit == d ? sub + 1 : 0);
		else if (sup) result += (sup - 1) * k + (digit ? k : sub + 1);
	}
	return result;
}

int main() {
	int L, U;
	std::cin >> L >> U;
	for (int i = 1; i < 10; ++i) cnt[i] = F(i, U);
	for (int i = 1; i < 10; ++i) cnt[i] -= F(i, L - 1);
	for (int i = 1; i < 10; ++i) result += cnt[i] * i;
	std::cout << result;
}