#include <iostream>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;
const int LEN = 1e9;
ull sieve[LEN / 72 / 63];
int primes[22];

//ll f(const int p, const int k, ll pro = 1, int cnt = 0, int i = 0) {
//	// std::cout << pro << ' ' << cnt << ' ' << primes[i] << '\n';
//	if (pro > k) return 0;
//	if (primes[i] >= p) return cnt ? (cnt & 1 ? -1 : 1) * (k / pro) : 0;
//	ll ret = 0;
//	ret += f(p, k, pro, cnt, i + 1);
//	ret += f(p, k, pro * primes[i], cnt + 1, i + 1);
//	return ret;
//}

ll f(const int p, const int k, ll pro = 1, int mu = 1, int i = 0) {
	if (pro > k) return 0;
	if (primes[i] >= p) return mu * (k / pro);
	ll ret = 0;
	ret += f(p, k, pro, mu, i + 1);
	ret += f(p, k, pro * primes[i], mu * -1, i + 1);
	return ret;
}

int bs(const int p, const int n) {
	int l = 1, r = LEN / p, m, ret = LEN + 1;
	while (l <= r) {
		m = l + r >> 1;
		// std::cout << m << '\n' << f(p, m) << '\n';
		if (f(p, m) >= n) {
			ret = std::min(ret, m * p);
			r = m - 1;
		}
		else l = m + 1;
	}
	return ret;
}

int N, P;

int main() {
	std::cin >> N >> P;
	if (P * P > LEN) std::cout << (N == 1 ? 1 : 0);
	else if (P < 72) {
		for (int i = 2, k = 0; i <= P; ++i) {
			if (sieve[i >> 6] & 1llu << (i & 63)) continue;
			primes[k++] = i;
			for (int j = i * 2; j <= P; j += i) sieve[j >> 6] |= 1llu << (j & 63);
		}
		int ret = bs(P, N);
		std::cout << (ret > LEN ? 0 : ret);
	}
	else {
		int len = LEN / P, ret = 0;
		for (int i = 2; i < P; ++i) {
			if (sieve[i >> 6] & 1llu << (i & 63)) continue;
			for (int j = i; j <= len; j += i) sieve[j >> 6] |= 1llu << (j & 63);
		}
		for (int i = 1, k = 0; i <= len; ++i) {
			if ((~sieve[i >> 6] & 1llu << (i & 63)) && ++k == N) {
				ret = i;
				break;
			}
		}
		std::cout << ret * P;
	}
}