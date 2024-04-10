#include <iostream>
#include <unordered_map>
#include <vector>

typedef long long ll;

const int LEN = 1'000'001;
int mu[LEN] = { 0, 1, };
std::unordered_map<ll, ll> dp;
void init() {
	for (int i = 1; i < LEN; ++i) {
		if (mu[i]) {
			for (int j = i << 1; j < LEN; j += i)
				mu[j] -= mu[i];
		}
	}
	dp[0] = 0;
	for (ll i = 1; i < LEN; ++i) dp[i] = dp[i - 1] + mu[i];
}
ll S(ll i) {
	if (dp.find(i) != dp.end()) return dp[i];
	ll s = 1;
	for (ll d = 2, j; d <= i; d = j + 1) {
		j = i / (i / d);
		s -= (j - d + 1) * S(i / d);
	}
	return dp[i] = s;
}
ll So(ll i) {
	ll s = 0;
	while (i) {
		s += S(i);
		i >>= 1;
	}
	return s;
}
ll Se(ll i) { return S(i) - So(i); }

ll f(ll n) {
	ll result = 0;
	for (ll i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		result += (n / i) * (n / i / 2) * (So(j) - So(i - 1));
		result += (n / i) * (n / i) * (Se(j) - Se(i - 1));
	}
	return result;
}

ll gcd(ll a, ll b) { return !b ? a : gcd(b, a % b); }
ll naive(ll l) {
	ll result = 0;
	for (ll m = 2; m <= l; ++m)
		for (ll n = 1; n < m; ++n)
			if (gcd(gcd(m * m + n * n, 2 * m * n), m * m - n * n) == 1)
				++result;
	return result;
}

ll solve(ll n) {
	ll i, j;
	ll res = 0;
	for (i = 1; i <= n; i = j + 2) {
		j = n / (n / i);
		if (!(j & 1)) j--;
		res += ((n / i) * ((n / i) >> 1)) * (So(j) - So(i - 1));
	}
	for (i = 2; i <= n; i = j + 2) {
		j = n / (n / i);
		if (j & 1)j--;
		res += ((n / i) * (n / i)) * (Se(j) - Se(i - 1));
	}
	return res;
}

int main() {
	init();
	ll L;
	std::cin >> L;
	std::cout << f(L);
}