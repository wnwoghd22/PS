#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef long long ll;
typedef long double ld;
const int LEN = 100'000;
const ld ERR = 1e-7;
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
	for (int i = 0; i < K; ++i) {
		P += S[i].p;
		Q += S[i].q;
	}
	return (ld)P / Q;
}

ld binary_search() {
	ld l = 0, r = 1, m, result = 0;
	while (l < r + ERR) {
		m = (l + r) / 2;
		ld cur = f(m);
		if (cur > 0) {
			result = std::max(result, cur);
			l = m + ERR;
		}
		else r = m - ERR;
	}
	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		std::cin >> S[i].p >> S[i].q;
	}

	std::cout << std::fixed;
	std::cout.precision(10);
	std::cout << binary_search();
}