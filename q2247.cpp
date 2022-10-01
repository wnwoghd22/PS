#include <iostream>
#include <cmath>

typedef long long int ll;
const ll MOD = 1'000'000;

int main() {
	ll N, result = 0;
	std::cin >> N;

	// O(n)
	/* for (ll i = 2; i <= N / 2; ++i) {
		result += i * (N / i - 1);
		result %= MOD;
	} */

	// O(sqrt(n))
	for (ll j, i = 2; i <= N; i = j + 1)
	{
		j = N / (N / i);
		result += ((j + i) * (j - i + 1) / 2) * (N / i - 1);
		result %= MOD;
	}

	std::cout << result;
}