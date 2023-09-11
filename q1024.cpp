#include <iostream>

typedef long long ll;

ll N, L;
ll a, k;

ll f(ll n, ll k) {
	ll l = 0, r = n, m, s;

	while (l <= r) {
		m = l + r >> 1;
		s = (m * 2 + k - 1) * k / 2;
		if (s == n) return m;
		if (s < n) l = m + 1;
		else r = m - 1;
	}
	return -1;
}

int main() {
	std::cin >> N >> L;

	for (k = L; k <= 100; ++k) if (~(a = f(N, k))) break;
	if (k > 100) std::cout << -1;
	else for (int i = 0; i < k; ++i) std::cout << a + i << ' ';
}