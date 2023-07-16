#include <iostream>

typedef long long ll;
const int LEN = 300'001;
const ll INF = 1e10 + 1;
ll K;
int mu[LEN] = { 0, 1, }; // mobius

ll f(ll x) { // square free
	ll cnt = 0;
	for (ll i = 1; i * i <= x; ++i)
		cnt += mu[i] * (x / (i * i));
	return cnt;
}

ll binary_search(ll x) {
	ll l = 0, r = x << 1, m, result = INF * 2;

	while (l <= r) {
		m = l + r >> 1;
		if (f(m) >= x) {
			if (m < result) result = m;
			r = m - 1;
		}
		else l = m + 1;
	}
	return result;
}

int main() {
	std::cin >> K;
	for (int i = 1; i < LEN; ++i) {
		if (!mu[i]) continue;
		for (int j = i * 2; j < LEN; j += i)
			mu[j] -= mu[i];
	}
	std::cout << binary_search(K);
}