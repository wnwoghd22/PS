#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>

typedef long long ll;
typedef long double ld;
const int LEN = 100'000;
const ld ERR = 1e-10;
struct Score {
	ll p, q;
	ld m() const { return (ld)p / q; }
	bool operator<(const Score& r) const {
		if (std::abs(m() - r.m()) < ERR) return q < r.q;
		return m() < r.m();
	}
} S[LEN];
bool comp(const Score& l, const Score& r) {
	ll dl = l.q - l.p, dr = r.q - r.p;
	if (dl == dr) return l.p > r.p;
	return dl < dr;
}
ll N, K, P, Q, Px, Qx;
ll _N, _K, _P[LEN], _Q[LEN];
std::priority_queue<Score> pq;

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> K;
	_K = K;
	for (int i = 0; i < N; ++i) {
		std::cin >> Px >> Qx;
		S[i].p = Px;
		S[i].q = Qx;
		_P[i] = Px;
		_Q[i] = Qx;
	}
	std::sort(S, S + N, comp);
	for (int i = 0; i < K; ++i) {
		P += S[i].p;
		Q += S[i].q;
	}

	std::cout << std::fixed;
	std::cout.precision(10);
	std::cout << (ld)P / Q;
	ld max = 0;
	ll bit = 0;
	for (int i = 0; i < (1 << N); ++i) {
		K = P = Q = 0;
		for (int j = 0; j < N; ++j) {
			if ((1 << j) & i) {
				++K;
				P += _P[j];
				Q += _Q[j];
			}
		}
		if (K == _K) {
			ld mean = (ld)P / Q;
			if (mean > max) {
				bit = i;
				max = mean;
			}
		}
	}
	std::cout << ' ' << max << ' ' << bit;
}