#include <iostream>

const int MOD = 1e9 + 7;
const int LEN = 1e5;

int N, A;

struct SegTree {
	int t[LEN << 2];
	void add(int x, int d, int s = 1, int e = N, int i = 1) {
		if (e < x || x < s) return;
		if (s == e) { t[i] = (t[i] + d) % MOD; return; }
		int m = s + e >> 1;
		add(x, d, s, m, i << 1); add(x, d, m + 1, e, i << 1 | 1);
		t[i] = (t[i << 1] + t[i << 1 | 1]) % MOD;
	}
	int get(int l, int r, int s = 1, int e = N, int i = 1) {
		if (e < l || r < s) return 0;
		if (l <= s && e <= r) return t[i];
		int m = s + e >> 1;
		return (get(l, r, s, m, i << 1) + get(l, r, m + 1, e, i << 1 | 1)) % MOD;
	}
} dp[11];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> A;
		dp[0].add(A, 1);
		for (int j = 1; j < 11; ++j)
			dp[j].add(A, dp[j - 1].get(1, A - 1));
	}
	std::cout << dp[10].get(1, N);
}