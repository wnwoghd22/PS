#include <iostream>
#include <cstring>

typedef long long ll;

int len, d[1000];

int f(ll x) {
	len = 0;
	while (x) {
		d[len++] = x % 10;
		x /= 10;
	}
	ll ret = 0;
	for (int i = 1; i <= 9; ++i) {
		for (int j = i + 1; j <= 9; ++j) {
			for (int k = 1; k < len; ++k) ret += (1 << k) - 2;
			// std::cout << i << ' ' << j << ' ' << ret << '\n';
			int b = 0;
			int bit = 0;
			for (int k = len - 1; k >= 0; --k) {
				if (k == 0) {
					if (bit & 2) ret += (d[0] >= i);
					if (bit & 1) ret += (d[0] >= j);
					break;
				}
				if (d[k] < i) break;

				if (d[k] == i) {
					if (~bit & 1) b++;
					bit |= 1;
					continue;
				}

				int c = b + !(bit & 1);
				ret += (1 << k) - 2 + c;

				if (d[k] < j) break;

				if (d[k] == j) {
					if (~bit & 2) b++;
					bit |= 2;
					continue;
				}

				if (d[k] > j) {
					int c = b + !(bit & 2);
					ret += (1 << k) - 2 + c;
					break;
				}
			}
		}
	}
	for (int i = 1; i <= 9; ++i) {
		for (int k = 1; k < len; ++k) ret += (1 << k - 1) - 1;
		if (d[len - 1] > i) ret += (1 << len - 1) - 1;
		else if (d[len - 1] == i) {
			int b = 1;
			int bit = 2;
			for (int k = len - 2; k >= 0; --k) {
				if (k == 0) {
					if (bit & 1) ret += (d[0] >= i);
					ret += (d[0] >= 0);
					break;
				}

				if (d[k] == 0) {
					if (~bit & 1) b++;
					bit |= 1;
					continue;
				}

				int c = b + !(bit & 1);
				ret += (1 << k) - 2 + c;
				
				if (d[k] < i) break;

				if (d[k] == i) continue;
				
				if (d[k] > i) {
					int c = b + !(bit & 2);
					ret += (1 << k) - 2 + c;
					break;
				}
			}
		}
	}

	return ret;
}

ll solve(ll n) {
	ll l = 10, r = 1e18, m, ret = 1e18;
	while (l <= r) {
		m = l + r >> 1;
		if (f(m) >= n) {
			ret = std::min(ret, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	return ret;
}

int main() {
	// std::cout << f(22) << '\n';

	ll N;
	while (1) {
		std::cin >> N;
		if (!N) break;
		std::cout << solve(N) << '\n';
	}
}