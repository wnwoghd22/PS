#include <cstring>

typedef long long ll;
const ll MOD = 1'000'000;
const int LEN = 1'000'000;

int c; // width
short seg_max[LEN << 2];
short seg_min[LEN << 2];
short lazy[LEN << 2];
ll s;

struct Result {
	int top;
	int count;
};

inline short max(short a, short b) { return a > b ? a : b; }
inline short min(short a, short b) { return a < b ? a : b; }

void propagate(int s, int e, int i) {
	if (lazy[i]) {
		seg_max[i] += lazy[i];
		seg_min[i] += lazy[i];
		if (s ^ e) {
			lazy[i << 1] += lazy[i];
			lazy[i << 1 | 1] += lazy[i];
		}
		lazy[i] = 0;
	}
}

void update(int l, int r, short d, int s = 0, int e = c - 1, int i = 1) {
	propagate(s, e, i);
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		seg_max[i] += d;
		seg_min[i] += d;
		if (s ^ e) {
			lazy[i << 1] += d;
			lazy[i << 1 | 1] += d;
		}
		return;
	}
	int m = s + e >> 1;
	update(l, r, d, s, m, i << 1);
	update(l, r, d, m + 1, e, i << 1 | 1);
	seg_max[i] = max(seg_max[i << 1], seg_max[i << 1 | 1]);
	seg_min[i] = min(seg_min[i << 1], seg_min[i << 1 | 1]);
}

inline short get_max() { return seg_max[1]; }
inline short get_min() { return seg_min[1]; }

void init(int C) {
	s = 0;
	c = C;
	memset(seg_max, 0, sizeof seg_max);
	memset(seg_min, 0, sizeof seg_min);
	memset(lazy, 0, sizeof lazy);
}

Result query(int l, int h, int w) {
	int r = l + w - 1;
	s += (ll)h * w;
	s %= MOD;

	update(l, r, h);
	int bottom = get_min();

	if (bottom) {
		s -= (ll)c * bottom;
		s = (s + MOD * MOD) % MOD;
		update(0, c - 1, -bottom);
	}
	int top = get_max();
	Result result;
	result.top = top;
	result.count = s;
	return result;
}