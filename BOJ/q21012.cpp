#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 200'001;
int N, Q, A;

struct Result {
	int cnt;
	ll sum;
	Result operator+(const Result& o) const { return { cnt + o.cnt, sum + o.sum }; }
};

struct PersistentSegTree {
	struct Node { int l, r, cnt; ll sum; } t[LEN * 20];
	int cur = 0, ptr[LEN];
	void update(int k, int x, int d) { update(ptr[k - 1], ptr[k] = ++cur, 1, LEN, x, d); }
	void update(int p, int i, int s, int e, int x, int d) {
		if (s == e) { t[i].cnt = t[p].cnt + 1; t[i].sum = t[p].sum + d; return; }
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
		t[i].sum = t[t[i].l].sum + t[t[i].r].sum;
	}
	int get_cnt(int k, int l, int r) { return get_cnt(ptr[k], l, r, 1, LEN); }
	int get_cnt(int i, int l, int r, int s, int e) {
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) { return t[i].cnt; }
		int m = s + e >> 1;
		return get_cnt(t[i].l, l, r, s, m) + get_cnt(t[i].r, l, r, m + 1, e);
	}

	ll get_sum(int k, int l, int r) { return get_sum(ptr[k], l, r, 1, LEN); }
	ll get_sum(int i, int l, int r, int s, int e) {
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) { return t[i].sum; }
		int m = s + e >> 1;
		return get_sum(t[i].l, l, r, s, m) + get_sum(t[i].r, l, r, m + 1, e);
	}

	Result get(int k, int l, int r) { return get(ptr[k], l, r, 1, LEN); }
	Result get(int i, int l, int r, int s, int e) {
		if (r < s || e < l) return { 0, 0 };
		if (l <= s && e <= r) { return { t[i].cnt, t[i].sum }; }
		int m = s + e >> 1;
		return get(t[i].l, l, r, s, m) + get(t[i].r, l, r, m + 1, e);
	}
} pst;

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A;
		pst.update(i, A, A);
	}

	std::cin >> Q;
	for (int i = 0, L, R, A, B, S; i < Q; ++i) {
		std::cin >> L >> R >> A >> B >> S;

		ll l = A, r = B, m, cnt, ret, sum, ans = 0;

		/* critical counter example : the objective function can have two points!
		 * let Ci is # of engineers whose potential is i,
		 * 1, 0, 0, 0, 0, 0, 0, ...
		 * if a person can be a team that has average over S, the answer should be 1.
		 * but by binary search, it cannot be caught.
		 *  how to resolve: find bound that includes at least one engineer.
		 */
		ret = A - 1;
		while (l <= r) {
			m = l + r >> 1;
			cnt = pst.get_cnt(R, m, B) - pst.get_cnt(L - 1, m, B);
			if (cnt > 0) {
				ret = std::max(ret, m);
				l = m + 1;
			}
			else r = m - 1;
		}
		if (ret < S) {
			std::cout << "0\n";
			continue;
		}

		l = A; r = ret; ret = B + 1;
		while (l <= r) {
			m = l + r >> 1;
			Result right = pst.get(R, m, B);
			Result left = pst.get(L - 1, m, B);
			sum = right.sum - left.sum;
			cnt = right.cnt - left.cnt;
			// sum = pst.get_sum(R, m, B) - pst.get_sum(L - 1, m, B);
			// cnt = pst.get_cnt(R, m, B) - pst.get_cnt(L - 1, m, B);
			if (sum >= cnt * S) {
				ret = std::min(ret, m);
				r = m - 1;
			}
			else l = m + 1;
		}

		if (ret == B + 1) std::cout << "0\n";
		else {
			Result right = pst.get(R, ret, B);
			Result left = pst.get(L - 1, ret, B);
			sum = right.sum - left.sum;
			cnt = right.cnt - left.cnt;
			// sum = pst.get_sum(R, ret, B) - pst.get_sum(L - 1, ret, B);
			// cnt = pst.get_cnt(R, ret, B) - pst.get_cnt(L - 1, ret, B);
			if (ret > A) {
				l = 0, r = pst.get_cnt(R, ret - 1, ret - 1) - pst.get_cnt(L - 1, ret - 1, ret - 1);
				while (l <= r) {
					m = l + r >> 1;
					if (sum + (ret - 1) * m >= (cnt + m) * S) {
						ans = std::max(ans, m);
						l = m + 1;
					}
					else r = m - 1;
				}
				cnt += ans;
			}
			std::cout << cnt << '\n';
		}
	}
}