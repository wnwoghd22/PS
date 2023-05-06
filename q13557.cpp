#include <iostream>
#include <algorithm>

typedef long long int ll;
const ll INF = 1e9;
const int LEN = 100'001;
struct SegNode {
	ll lmax, rmax, max, sum;
	const SegNode operator+=(const int& r) {
		lmax = rmax = max = sum += r;
		return *this;
	}
	SegNode operator+(const SegNode& r) const {
		return {
			std::max(lmax, sum + r.lmax),
			std::max(rmax + r.sum, r.rmax),
			std::max({max, r.max, rmax + r.lmax}),
			sum + r.sum
		};
	}
} seg_tree[LEN * 4];
int N, M, A, i;

void update(int k, ll d, int s = 1, int e = N, int i = 1) {
	if (k < s || e < k) return;
	if (s == e) { seg_tree[i] += d; return; }
	int m = s + e >> 1;
	update(k, d, s, m, i << 1); update(k, d, m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] + seg_tree[i << 1 | 1];
}

SegNode get_max(int l, int r, int s = 1, int e = N, int i = 1) {
	if (e < l || r < s) return { -INF, -INF, -INF, 0 };
	if (l <= s && e <= r) return seg_tree[i];
	int m = s + e >> 1;
	return get_max(l, r, s, m, i << 1) + get_max(l, r, m + 1, e, i << 1 | 1);
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (i = 1; i <= N; ++i) {
		std::cin >> A;
		update(i, A);
	}
	std::cin >> M;
	int x1, x2, y1, y2;
	while (M--) {
		std::cin >> x1 >> y1 >> x2 >> y2;
		if (y1 < x2) {
			SegNode l = get_max(x1, y1);
			SegNode r = get_max(x2, y2);
			SegNode m = get_max(y1 + 1, x2 - 1);
			std::cout << l.rmax + m.sum + r.lmax << '\n';
		}
		else {
			SegNode l = get_max(x1, x2);
			SegNode r = get_max(y1, y2);
			SegNode m = get_max(x2 + 1, y1 - 1);
			std::cout << std::max({
				m.max,
				l.rmax + m.lmax,
				m.rmax + r.lmax,
				l.rmax + m.sum + r.lmax
			}) << '\n';
		}
	}
}