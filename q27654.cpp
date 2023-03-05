#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef long long ll;
typedef long double ld;
const int LEN = 100'000;
const ld ERR = 1e-10;
struct Score {
	ll p, q;
	ld m() const { return (ld)p / q; }
} S[LEN];
ll N, K, P, Q, Px, Qx;

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		std::cin >> Px >> Qx;
		S[i].p = Px;
		S[i].q = Qx;
	}
	std::sort(S, S + N);
	for (int i = 0; i < K; ++i) {
		P += S[i].p;
		Q += S[i].q;
	}

	std::cout << std::fixed;
	std::cout.precision(10);
	std::cout << (ld)P / Q;
}