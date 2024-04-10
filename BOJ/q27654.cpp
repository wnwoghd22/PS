#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef long long ll;
typedef long double ld;
const int LEN = 100'000;
const ld ERR = 1e-6;
ld x;
struct Score {
	ll p, q;
	ld f(ld x) const { return -q * x + p; }
	bool operator<(const Score& r) { return f(x) > r.f(x); }
} S[LEN];
ll N, K;

ld f(ld m) {
	x = m;
	std::sort(S, S + N);
	ll P = 0, Q = 0;
	ld result = 0;
	for (int i = 0; i < K; ++i) result += S[i].f(x);
	return result;
}

ld binary_search() {
	ll l = 0, r = 1000000, m;
	ld result = 0;
	while (l <= r) {
		m = l + r >> 1;
		ld cur = f(ld(m) / 1000000);
		if (cur > 0) {
			result = std::max(result, ld(m) / 1000000);
			l = m + 1;
		}
		else r = m - 1;
	}
	return result;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		std::cin >> S[i].p >> S[i].q;
	}

	std::cout << std::fixed;
	std::cout.precision(10);
	std::cout << binary_search();
}