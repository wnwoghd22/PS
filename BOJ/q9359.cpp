#include <iostream>
#include <vector>

typedef long long ll;
const int LEN = 33e3;
bool sieve[LEN];
std::vector<int> primes;

void init() {
	primes.clear();
	for (int i = 2; i < LEN; ++i) {
		if (sieve[i]) continue;
		primes.push_back(i);
		for (int j = i * 2; j < LEN; j += i)
			sieve[j] = true;
	}
}

std::vector<int> f(int n) {
	std::vector<int> factors;
	for (const int& p : primes) {
		if (!(n % p)) factors.push_back(p);
		while (!(n % p)) n /= p;
	}
	if (n > 1) factors.push_back(n);
	return factors;
}

ll f(ll k, std::vector<int>& v) {
	ll cnt = 0;
	for (int i = 1; i < 1 << v.size(); ++i) {
		ll den = 1, s = 0;
		for (int j = 0; j < v.size(); ++j) {
			if (i & (1 << j))
				den *= v[j], ++s;
		}
		if (s & 1) cnt += k / den;
		else cnt -= k / den;
	}
	return k - cnt;
}

int main() {
	init();

	ll T, A, B, N;
	std::cin >> T;
	for (int t = 1; t <= T; ++t) {
		std::cin >> A >> B >> N;
		std::vector<int> fs = f(N);
		std::cout << "Case #" << t << ": " << f(B, fs) - f(A - 1, fs) << '\n';
	}
}