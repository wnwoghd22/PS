#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

typedef long long ll;
const int LEN = 300'001;
const ll MOD = 1e9 + 7;
int K, N, rank = 1, A[LEN], f[LEN] = { 1, };

struct PersistentSegTree {
	struct Node { int l, r, cnt, sum; } t[LEN << 5];
	int cur = 0, ptr[LEN];
	void init(int i, int s, int e) {
		if (s == e) return;
		int m = s + e >> 1;
		t[i].l = ++cur; t[i].r = ++cur;
		init(t[i].l, s, m); init(t[i].r, m + 1, e);
	}
	void update(int k, int x, int d) { update(ptr[k - 1], ptr[k] = ++cur, 1, K, x, d); }
	void update(int p, int i, int s, int e, int x, int d) {
		if (s == e) { t[i].cnt += 1; t[i].sum += d; return; }
		int m = s + e >> 1;
		if (x <= m) { // update left
			t[i].l = ++cur; t[i].r = t[p].r;
			update(t[p].l, t[i].l, s, m, x, d);
		}
		else {
			t[i].r = ++cur; t[i].l = t[p].l;
			update(t[p].r, t[i].r, m + 1, e, x, d);
		}
		t[i].cnt = t[t[i].l].cnt + t[t[i].r].cnt;
		t[i].sum = (t[t[i].l].sum + t[t[i].r].sum) % MOD;
	}
	int get_cnt(int k, int l, int r) { return get_cnt(ptr[k], l, r, 1, K); }
	int get_cnt(int i, int l, int r, int s, int e) {
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) { return t[i].cnt; }
		int m = s + e >> 1;
		return get_cnt(t[i].l, l, r, s, m) + get_cnt(t[i].r, l, r, m + 1, e);
	}

	int get_sum(int k, int l, int r) { return get_sum(ptr[k], l, r, 1, K); }
	int get_sum(int i, int l, int r, int s, int e) {
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) { return t[i].sum; }
		int m = s + e >> 1;
		return (get_sum(t[i].l, l, r, s, m) + get_sum(t[i].r, l, r, m + 1, e)) % MOD;
	}
} pst;

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> K >> N;
	for (ll i = 1; i <= K; ++i) f[i] = i * f[i - 1] % MOD; // preprocess
	for (int i = 0; i < K; ++i) std::cin >> A[K - i];

	pst.init(0, 1, K);
	for (int k = 1; k <= K; ++k) {
		rank = (rank + (ll)f[k - 1] * pst.get_cnt(k - 1, 0, A[k] - 1)) % MOD;
		pst.update(k, A[k], f[k - 1]);
	}
	std::cout << rank << '\n';
	for (int i = 0, a, b; i < N; ++i) {
		int ans = rank;
		std::cin >> a >> b;
		a = K - a + 1; b = K - b + 1;
		if (A[a] > A[b]) {
			// std::cout << "switching: " << A[a] << ' ' << A[b] << '\n';
			// std::cout << "r cnt: " << pst.get_cnt(b - 1, A[a], A[b]) << '\n';
			ans = (ans + (ll)f[b - 1] * pst.get_cnt(b - 1, A[b], A[a])) % MOD;
			ans = (ans - (ll)f[a - 1] * pst.get_cnt(a - 1, A[b], A[a]) + MOD * MOD) % MOD;
			ans = (ans - pst.get_sum(a - 1, A[b] + 1, A[a] - 1) + pst.get_sum(b - 1, A[b] + 1, A[a] - 1) + MOD) % MOD;
		}
		else {
			// std::cout << "switching: " << A[a] << ' ' << A[b] << '\n';
			// std::cout << "r cnt: " << pst.get_cnt(b - 1, A[a], A[b]) << '\n';
			ans = (ans - (ll)f[b - 1] * pst.get_cnt(b - 1, A[a], A[b]) + MOD * MOD) % MOD;
			ans = (ans + (ll)f[a - 1] * pst.get_cnt(a, A[a], A[b] - 1)) % MOD;
			ans = (ans + pst.get_sum(a - 1, A[a] + 1, A[b] - 1) - pst.get_sum(b - 1, A[a] + 1, A[b] - 1) + MOD) % MOD;
		}
		std::cout << ans << '\n';
	}
}