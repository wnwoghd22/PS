#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 100'001;

int N;
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
	int max, lm, rm, sum;
	LenNode operator+(const LenNode& r) const {
		return {
			std::max(max, r.max),
			std::max(lm, lm && rm ? sum + r.lm : 0),
			std::max(r.lm && r.rm ? rm + r.sum : 0, r.rm),
			std::max({ max, r.max, rm + r.lm })
		};
	}
} seg_len[LEN * 4];
void update(int x, int d, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) {
		seg_len[i] = { 1, 1, 1, 1 };
		return;
	}
	int m = s + e >> 1;
	update(x, d, s, m, i << 1);
	update(x, d, m + 1, e, i << 1 | 1);
	seg_len[i] = seg_len[i << 1] + seg_len[i << 1 | 1];
}

int main() {
	std::cin >> N;

}