#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
const int LEN = 500'000;
struct Company {
	int t, p;
	bool operator<(const Company& r) const { return t == r.t ? p < r.p : t < r.t; }
} seller[LEN], buyer[LEN];
std::vector<Company> S, B;
int N, M;

ll c(int i, int j) {
	ll dx = B[j].p - S[i].p;
	ll dy = B[j].t - S[i].t;
	return dx < 0 && dy < 0 ? 0 : dx * dy;
}

ll f(int s, int e, int l, int r) {
	if (s > e) return 0;
	ll benefit;
	int opt = l, m = s + e >> 1;

	for (int i = opt; i <= r; ++i) {
		if (c(m, i) > c(m, opt)) opt = i;
	}
	benefit = c(m, opt);

	return std::max({ benefit, f(s, m - 1, l, opt), f(m + 1, e, opt, r) });
}

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> M >> N;
	for (int i = 0; i < M; ++i) std::cin >> seller[i].p >> seller[i].t;
	for (int i = 0; i < N; ++i) std::cin >> buyer[i].p >> buyer[i].t;
	std::sort(seller, seller + M);
	std::sort(buyer, buyer + N);

	// make monotonic
	for (int i = 0; i < M; ++i) {
		if (S.empty() || seller[i].p < S.back().p)
			S.push_back(seller[i]);
	}
	for (int i = 0; i < N; ++i) {
		while (B.size() && buyer[i].p >= B.back().p) B.pop_back();
		B.push_back(buyer[i]);
	}
	std::cout << f(0, S.size() - 1, 0, B.size() - 1);
}