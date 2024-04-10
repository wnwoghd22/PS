#include <iostream>

typedef long long ll;
const int LEN = 1e6 + 1;
const int P = 917, MOD = 993244853;

int N, Q;
ll p[LEN];
char S[LEN];

struct seg {
	ll t[LEN << 2];
	void update(int x, int d, int s = 0, int e = N - 1, int i = 1) {
		if (x < s || e < x) return;
		if (s == e) {
			t[i] = d * p[i] % MOD;
			return;
		}
		int m = s + e >> 1;
		update(x, d, s, m, i << 1); update(x, d, m + 1, e, i << 1 | 1);
		t[i] = (t[i << 1] + t[i << 1 | 1]) % MOD;
	}
} s1, s2;

int main() {
	std::cin >> N >> Q >> S;
	p[0] = MOD;
	for (int i = 1; i <= N; ++i) p[i] = p[i - 1] * P % MOD;
	for (int i = 1; i <= N; ++i) {
		s1.update(i, S[i - 1]);
		s2.update(N - i + 1, S[N - i]);
	}
	for (int i = 1, l, r; i <= Q; ++i) {
		std::cin >> l >> r;

	}
}