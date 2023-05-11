#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 100'001;

int N, M, A[LEN];
struct SeqNode { ll a0, d; } seg_seq[LEN * 4];
void update_seq(int l, int r, ll a0, ll d, int s = 1, int e = N, int i = 1) {
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		seg_seq[i].a0 += a0 + (s - l) * d;
		seg_seq[i].d += d;
		return;
	}
	int m = s + e >> 1;
	update_seq(l, r, a0, d, s, m, i << 1);
	update_seq(l, r, a0, d, m + 1, e, i << 1 | 1);
}
ll get_seq(int x, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return 0;
	ll result = seg_seq[i].a0 + (x - s) * seg_seq[i].d;
	if (s == e) return result;
	int m = s + e >> 1;
	return result + get_seq(x, s, m, i << 1) + get_seq(x, m + 1, e, i << 1 | 1);
}

struct LenNode {
	int max, lm, rm, full;
	LenNode operator+(const LenNode& r) const {
		return {
			std::max({ max, r.max, rm + r.lm }),
			full ? max + r.lm : lm,
			r.full ? rm + r.max : r.rm,
			full & r.full
		};
	}
} seg_len[LEN * 4];
void update_len(int x, int d, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) {
		seg_len[i] = { d, d, d, d };
		return;
	}
	int m = s + e >> 1;
	update_len(x, d, s, m, i << 1);
	update_len(x, d, m + 1, e, i << 1 | 1);
	seg_len[i] = seg_len[i << 1] + seg_len[i << 1 | 1];
}
LenNode get_len(int l, int r, int s = 1, int e = N, int i = 1) {
	if (e < l || r < s) return { 0, 0, 0, 0 };
	if (l <= s && e <= r) return seg_len[i];
	int m = s + e >> 1;
	return get_len(l, r, s, m, i << 1) + get_len(l, r, m + 1, e, i << 1 | 1);
}

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		update_seq(i, i, A[i], 0);
		if (i >= 3)
			update_len(i, A[i - 1] << 1 == A[i] + A[i - 2]);
	}
	std::cin >> M;
	for (int m = 0, q, i, j, x, y; m < M; ++m) {
		std::cin >> q >> i >> j;
		if (q == 1) {
			std::cin >> x >> y;
			update_seq(i, j, x, y);
			if (i >= 2) {
				int l1 = get_seq(i - 1), l2 = get_seq(i), l3 = get_seq(i + 1);
				update_len(i + 1, l2 << 1 == l1 + l3);
			}
			if (i >= 3) {
				int l1 = get_seq(i - 2), l2 = get_seq(i - 1), l3 = get_seq(i);
				update_len(i, l2 << 1 == l1 + l3);
			}
			if (j < N) {
				int r1 = get_seq(j - 1), r2 = get_seq(j), r3 = get_seq(j + 1);
				update_len(j + 1, r2 << 1 == r1 + r3);
			}
			if (j < N - 1) {
				int r1 = get_seq(j), r2 = get_seq(j + 1), r3 = get_seq(j + 2);
				update_len(j + 2, r2 << 1 == r1 + r3);
			}
		}
		if (q == 2) std::cout << (j - i == 1 ? 2 : get_len(i + 2, j).max + 2) << '\n';
	}
}