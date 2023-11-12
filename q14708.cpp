#include <iostream>
#include <algorithm>

typedef long long ll;

ll K;
ll A[3];
ll a, b, c;
ll cur = 1e18;

int main() {
	std::cin >> K;
	ll l = 1, r = a = 1e6, m;
	while (l <= r) {
		m = l + r >> 1;
		if (m * m * m >= K) {
			a = std::min(m, a);
			r = m - 1;
		}
		else l = m + 1;
	}
	// std::cout << a << '\n';
	for (ll i = std::max(1ll, a - 3000); i <= a + 1; ++i) {
		ll K2 = K / i + 1;
		b = sqrt(K2) + 1;
		for (ll j = std::max(1ll, b - 4000); j <= b + 1; ++j) {
			ll c = K2 / j + 1;
			while (i * j * c > K) --c;
			while (i * j * c < K) ++c;
			// std::cout << a << ' ' << b << ' ' << c << '\n';
			ll now = (i + j) * 2 * c + i * j * 2;
			if (now < cur) {
				cur = now;
				A[0] = i, A[1] = j, A[2] = c;
				std::sort(A, A + 3);
			}
		}
	}
	// std::cout << cur << '\n';
	std::cout << A[0] << ' ' << A[1] << ' ' << A[2];
}