#include <iostream>

const int LEN = 3'000'001;

class SplayTree {

} st[LEN];

int N, A[LEN];

struct SegMax {
	int seg_max[LEN << 2];
	void update(int x, int d, int s = 1, int e = N, int i = 1) {
		if (x < s || e < x) return;
		if (s == e) { seg_max[i] = d; return; }
		int m = s + e >> 1;
		update(x, d, s, m, i << 1);
		update(x, d, m + 1, e, i << 1 | 1);
		seg_max[i] = std::max(seg_max[i << 1], seg_max[i << 1 | 1]);
	}
	int get_max(int l, int r, int s = 1, int e = N, int i = 1) {
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) { return seg_max[i]; }
		int m = s + e >> 1;
		return std::max(get_max(l, r, s, m, i << 1), get_max(l, r, m + 1, e, i << 1 | 1));
	}
} depth, signals;

int get_rightmost(int i) {
	int l = i + 1, r = N, m, j = N + 1;
	while (l <= r) {
		m = l + r >> 1;
		if (depth.get_max(l, r) > A[i]) {
			j = std::min(m, j);
			r = m - 1;
		}
		else l = m + 1;
	}
	return j;
}