#include <iostream>
#include <algorithm>

const int LEN = 2e5 + 1;

int seg_max[LEN << 2], lazy[LEN << 2];

void propagate(int s, int e, int i) {
	if (lazy[i]) {
		seg_max[i] += lazy[i];
		if (s ^ e) {
			lazy[i << 1] += lazy[i];
			lazy[i << 1 | 1] += lazy[i];
		}
		lazy[i] = 0;
	}
}

void update(int l, int r, short d, int s = 1, int e = LEN, int i = 1) {
	propagate(s, e, i);
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		seg_max[i] += d;
		if (s ^ e) {
			lazy[i << 1] += d;
			lazy[i << 1 | 1] += d;
		}
		return;
	}
	int m = s + e >> 1;
	update(l, r, d, s, m, i << 1);
	update(l, r, d, m + 1, e, i << 1 | 1);
	seg_max[i] = std::max(seg_max[i << 1], seg_max[i << 1 | 1]);
}

int get_max() { return seg_max[1]; }

struct Query {
	int t, x, d;
	bool operator<(const Query& r) const { return t < r.t; }
} q[LEN << 1];

int N, D, W;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> D >> W;
	for (int i = 0, t, x; i < N; ++i) {
		std::cin >> t >> x;
		q[i << 1] = { t, x, 1 };
		q[i << 1 | 1] = { t + D, x, -1 };
	}
	std::sort(q, q + N * 2);
	int ret = 0;
	for (int i = 0; i < N * 2; ++i) {
		while (1) {
			// std::cout << q[i].t << ' ' << q[i].x << ' ' << q[i].d << '\n';
			update(q[i].x, q[i].x + W - 1, q[i].d);
			if (i == N * 2 - 1) break;
			if (q[i + 1].t == q[i].t) ++i;
			else break;
		}
		// std::cout << "cur: " << q[i].t << ' ' << get_max() << '\n';
		ret = std::max(ret, get_max());
	}
	std::cout << ret;
}