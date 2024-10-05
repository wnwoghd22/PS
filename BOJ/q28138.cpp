#include <iostream>

typedef long long ll;

ll N, R, K, sum;

int main() {
	std::cin >> N >> R;
	K = N - R;

	for (ll i = 1; i * i <= K; ++i) {
		if (K % i == 0) {
			ll j = K / i;
			if (i > R) sum += i;
			if (i != j && j > R) sum += j;
		}
	}
	std::cout << sum;
}