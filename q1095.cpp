#include <iostream>

typedef long long ll;
const int LEN = 100'001;

ll S, F, M;
ll sieve[LEN], cnt[LEN];

ll fn(ll k, ll p) {
	ll c = 0, n = 1;
	while ((n *= p) <= k) c += k / n;
	return c;
}

void init() {
	for (int i = 2; i <= M; ++i) {
		if (sieve[i]) continue;
		cnt[i] = fn(S + F, i) - fn(S, i) - fn(F, i);
		for (int j = i; j <= M; j += i)
			sieve[j] = i;
	}
}

bool is_factor(int m) {
	int p = sieve[m];
	int c = 1;
	while (m > 1) {
		if (c > cnt[p]) return false;
		m /= p;
		if (sieve[m] == p) ++c;
		else p = sieve[m], c = 1;
	}
	return true;
}

int main() {
	std::cin >> S >> F >> M;
	init();
	for (int i = M; i; --i) {
		if (is_factor(i)) {
			std::cout << i;
			break;
		}
	}
}