#include <iostream>

typedef long long int ll;
typedef std::pair<ll, std::pair<ll, ll>> GCD;
const ll INF = 1e9;

GCD EE(ll a, ll b) {
	ll r0 = a, r1 = b;
	ll s0 = 1, s1 = 0;
	ll t0 = 0, t1 = 1;
	ll temp = 0, q = 0;

	while (r1) {
		q = r0 / r1;
		temp = r0, r0 = r1, r1 = temp - r1 * q;
		temp = s0, s0 = s1, s1 = temp - s1 * q;
		temp = t0, t0 = t1, t1 = temp - t1 * q;

		if (s0 > INF || t0 > INF) return { -1, {INF, INF} };
	}

	return { r0, {s0, t0} };
}


int main() {
	int T;
	std::cin >> T;
	while (T--) {
		ll K, C;
		std::cin >> K >> C;
		auto [g, p] = EE(C, K);
		auto [s, t] = p;
		if (g != 1) {
			std::cout << "IMPOSSIBLE\n";
			continue;
		}
		if (C == 1) {
			if (K == INF) std::cout << "IMPOSSIBLE\n";
			else std::cout << K + 1 << '\n';
			continue;
		}
		if (K == 1) {
			std::cout << 1 << '\n';
			continue;
		}

		while (s < 0) s += K;

		std::cout << s << '\n';
	}
}