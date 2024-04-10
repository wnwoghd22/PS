#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 2e5;

int N, T;

struct SegNode {
	int l, r, lz, cnt = 1;
	SegNode operator+(const SegNode& n) const { return { ~l ? l : n.r, ~n.r ? n.r : r, 0, cnt + n.cnt - (r == n.l) }; }
} seg[LEN << 2];

void propagate(int s, int e, int i) {
	if (seg[i].lz) {
		seg[i].l ^= 1; seg[i].r ^= 1;
		if (s ^ e) {
			seg[i << 1].lz ^= 1;
			seg[i << 1 | 1].lz ^= 1;
		}
		seg[i].lz = 0;
	}
}

SegNode get(int l, int r, int s = 0, int e = N << 1 | 1, int i = 1) {
	propagate(s, e, i);
	if (r < s || e < l) return { -1, -1, 0, 0 };
	if (l <= s && e <= r) return seg[i];
	int m = s + e >> 1;
	return get(l, r, s, m, i << 1) + get(l, r, m + 1, e, i << 1 | 1);
}
void flip(int l, int r, int s = 0, int e = N << 1 | 1, int i = 1) {
	propagate(s, e, i);
	if (r < s || e < l) return;
	if (l <= s && e <= r) {
		seg[i].lz ^= 1;
		propagate(s, e, i);
		return;
	}
	int m = s + e >> 1;
	flip(l, r, s, m, i << 1); flip(l, r, m + 1, e, i << 1 | 1);
	seg[i] = seg[i << 1] + seg[i << 1 | 1];
}

struct Query {
	int y, l, r, d;
	bool operator<(const Query& q) const { return y < q.y; }
} q[LEN];

ll W, B;
ll cntB, cntW;
ll mergeB, mergeW;

int main() {
	std::cin >> N >> T;
	for (int i = 0, l, r, u, d; i < N; ++i) {
		std::cin >> l >> d >> r >> u;
		q[i << 1] = { d, l, r, 1 };
		q[i << 1 | 1] = { u, l, r, -1 };
	}
	std::sort(q, q + 2 * N);
	for (int i = 0, cw, cb, mw, mb, rw, rb; i < 2 * N; ++i) {
		if (q[i].d == 1) flip(q[i].l, q[i].r); // add query
			
		cw = (seg[1].cnt + 1) / 2;
		cb = seg[1].cnt - cw;
		SegNode range = get(q[i].l, q[i].r);
		if (range.l) { // BWBW...
			rb = (range.cnt + 1) / 2;
			rw = range.cnt - rb;
		}
		else { // WBWB...
			rw = (range.cnt + 1) / 2;
			rb = range.cnt - rw;
		}
		mw = cw - rw;
		mb = cb - rb;
		
		if (q[i].d == -1) { // remove query
			flip(q[i].l, q[i].r);
			cw -= rw;
			cb -= rb;
		}

		cntB += cb; cntW += cw;
		mergeB += mb; mergeW += mw;

		std::cout << cw << ' ' << cb << ' ' << mw << ' ' << mb << '\n';
	}
	W = cntW - mergeW + 1;
	B = cntB - mergeB;
	if (T == 1) std::cout << W + B;
	else std::cout << W << ' ' << B;
}