#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef long long int ll;
const int LEN = 100'000;
int N, D, T[LEN], V[LEN];

ll c(ll i, ll j) { return (j - i) * T[j] + V[i]; }
ll f(int s, int e, int l, int r) {
	if (s > e) return 0;
	int m = s + e >> 1;
	int opt = std::max(l, m - D);
	for (int i = opt; i <= std::min(m, r); ++i)
		if (c(i, m) > c(opt, m))
			opt = i;
	
	return std::max({ c(opt, m), f(s, m - 1, l, opt), f(m + 1, e, opt, r) });
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> D;
	for (int i = 0; i < N; ++i) std::cin >> T[i];
	for (int i = 0; i < N; ++i) std::cin >> V[i];
	std::cout << f(0, N - 1, 0, N - 1);
}