#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

const int LEN = 500'000;
struct Company {
	int t, p;
	bool operator<(const Company& r) const { return t == r.t ? p > r.p : t < r.t; }
} seller[LEN], buyer[LEN];
int N, M;

int binary_search(int e) { // get upper bound
	int l = 0, r = M, m;
	while (l < r) {
		m = l + r >> 1;
		if (seller[m].t <= e) l = m + 1;
		else r = m;
	}
	return r;
}

int c(int i, int j) { return buyer[j].p - seller[i].p; }

int f(int s, int e, int l, int r) {
	if (s > e) return 0;
	int opt = l, benefit = 0;
	int m = s + e >> 1;
	int bound = binary_search(buyer[m].t) - 1;

	if (l <= bound) {
		for (int i = opt; i <= std::min(r, bound); ++i) {
			if (c(i, m) > c(opt, m)) opt = i;
		}
		benefit = c(opt, m);
	}

	return std::max({ benefit, f(s, m - 1, l, opt), f(m + 1, e, opt, r) });
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> M >> N;
	for (int i = 0; i < M; ++i) std::cin >> seller[i].p >> seller[i].t;
	for (int i = 0; i < N; ++i) std::cin >> buyer[i].p >> buyer[i].t;
	std::sort(seller, seller + M);
	std::sort(buyer, buyer + N);
	std::cout << f(0, N - 1, 0, M - 1);
}