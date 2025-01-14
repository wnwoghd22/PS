#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 3e5 + 10;
const ll INF = 1e17;

int len;
struct SegTree {
	ll t[LEN << 2];
	void init(int l, int r, int i) {
		t[i] = INF;
		if (l == r) return;
		int m = l + r >> 1;
		init(l, m, i << 1); init(m + 1, r, i << 1 | 1);
	}
	void update(ll x, int l, int r, int s = 1, int e = len, int i = 1) {
		if (e < l || r < s) return;
		if (l <= s && e <= r) {
			t[i] = std::min(t[i], x);
			return;
		}
		int m = s + e >> 1;
		update(x, l, r, s, m, i << 1);
		update(x, l, r, m + 1, e, i << 1 | 1);
	}
	ll query(int x, int s = 1, int e = len, int i = 1) {
		if (x < s || e < x) return INF;
		if (s == e) return t[i];
		int m = s + e >> 1;
		return std::min(t[i], std::min(query(x, s, m, i << 1), query(x, m + 1, e, i << 1 | 1)));
	}
} left, right;

struct Pos {
	int p, i;
	bool operator<(const Pos& o) const { return p < o.p; }
} p[LEN];
int N, X[LEN], t[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	std::cin >> t[0] >> t[N + 1];
	p[0].p = t[0]; p[0].i = 0;
	p[N + 1].p = t[N + 1]; p[N + 1].i = N + 1;
	ll base = 0, cost = 0;
	for (int i = 1; i <= N; ++i) {
		std::cin >> t[i];
		p[i].p = t[i];
		p[i].i = i;
		base += std::abs(t[i] - t[i - 1]);
	}
	std::sort(p, p + N + 2);
	X[p[0].i] = len = 1;
	for (int i = 1; i < N + 2; ++i) {
		if (p[i - 1].p != p[i].p) len++;
		X[p[i].i] = len;
	}

	left.init(1, len, 1); left.update(t[N + 1], 1, X[N + 1]);
	right.init(1, len, 1); right.update(-t[N + 1], X[N + 1], len);
	for (int i = 1; i <= N; ++i) {
		ll l = left.query(X[i]) - t[i];
		ll r = right.query(X[i]) + t[i];
		ll min = std::min(l, r) - std::abs(t[i] - t[i - 1]); 
		left.update(min + t[i - 1], 1, X[i - 1]);
		right.update(min - t[i - 1], X[i - 1], len);
		cost = std::min(cost, min);
	}
	std::cout << base + cost;
}