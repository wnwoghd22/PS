#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 2e5 + 2;

int N, len, T;
ll fenwick[LEN];
ll sum(int i) {
	ll result = 0;
	while (i > 0) {
		result += fenwick[i];
		i -= i & -i;
	}
	return result;
}
void update(int i, ll d) {
	while (i <= len) {
		fenwick[i] += d;
		i += i & -i;
	}
}
void update(int l, int r, ll d) {
	update(l, d);
	update(r, d);
}

struct Query {
	int y, l, r, d;
	bool operator<(const Query& q) const { return y < q.y; }
} q[LEN];

ll W, B;
ll cntB, cntW;
ll mergeB, mergeW;

int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> N >> T; 
	len = N << 1 | 1;
	for (int i = 0, l, r, u, d; i < N; ++i) {
		std::cin >> l >> d >> r >> u;
		q[i << 1] = { d, l, r, 1 };
		q[i << 1 | 1] = { u, l, r, -1 };
	}
	std::sort(q, q + 2 * N);
	for (int i = 0, l, r, cw, cb, mw, mb, rw, rb, cnt; i < 2 * N; ++i) {
		if (q[i].d == 1) { // add query
			update(q[i].l, q[i].r, q[i].d);
			cnt = sum(len) + 1;
			cw = cnt + 1 >> 1;
			cb = cnt - cw;
			l = sum(q[i].l);
			r = sum(q[i].r);
			if (l & 1) { // BWBW...
				rb = (r - l + 1) / 2;
				rw = r - l - rb;
			}
			else {
				rw = (r - l + 1) / 2;
				rb = r - l - rw;
			}
			mw = cw - rw; mb = cb - rb;
			cntW += cw; cntB += cb;
			mergeW += mw; mergeB += mb;
		}
		else {
			cnt = sum(len) + 1;
			cw = cnt + 1 >> 1;
			cb = cnt - cw;
			l = sum(q[i].l);
			r = sum(q[i].r);
			if (l & 1) { // BWBW...
				rb = (r - l + 1) / 2;
				rw = r - l - rb;
			}
			else {
				rw = (r - l + 1) / 2;
				rb = r - l - rw;
			}
			mw = cw - rw; mb = cb - rb;
			update(q[i].l, q[i].r, q[i].d);
			cnt = sum(len) + 1;
			cw = cnt + 1 >> 1;
			cb = cnt - cw;
			if (r - l == 1) {
				if (l & 1) mw -= 1;
				else mb -= 1;
			}
			cntW += cw; cntB += cb;
			mergeW += mw; mergeB += mb;
		}

		// std::cout << cw << ' ' << cb << ' ' << mw << ' ' << mb << '\n';
	}
	W = cntW - mergeW + 1;
	B = cntB - mergeB;
	if (T == 1) std::cout << W + B;
	else std::cout << W << ' ' << B;
}