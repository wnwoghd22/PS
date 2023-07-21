#include <iostream>
#include <vector>

const int LEN = 100'001;

int N;

struct SegCount {
	bool t[LEN << 2];
	void update(int l, int r, int d, int s = 1, int e = N, int i = 1) {
		if (r < s || e < l) return;
		if (l <= s && e <= r) { t[i] += d; return; }
		int m = s + e >> 1;
		update(l, r, d, s, m, i << 1);
		update(l, r, d, m + 1, e, i << 1 | 1);
	}
	bool get(int x, int s = 1, int e = N, int i = 1) {
		if (x < s || e < x) return 0;
		if (s == e) { return t[i]; }
		int m = s + e >> 1;
		return t[i] + get(x, s, m, i << 1) + get(x, m + 1, e, i << 1 | 1);
	}
} dpW, dpB;

struct SegConnect {
	bool t[LEN << 2];
	void update(int x, bool b, int s = 1, int e = N, int i = 1) {
		if (x < s || e < x) return;
		if (s == e) { t[i] = b; return; }
		int m = s + e >> 1;
		update(x, b, s, m, i << 1);
		update(x, b, m + 1, e, i << 1 | 1);
		t[i] = t[i << 1] && t[i << 1 | 1];
	}
	bool get(int l, int r, int s = 1, int e = N, int i = 1) {
		if (r < s || e < l) return 1;
		if (l <= s && e <= r) return t[i];
		int m = s + e >> 1;
		return get(l, r, s, m, i << 1) && get(l, r, m + 1, e, i << 1 | 1);
	}
} w, b;

/*
 * TODO:
 * finding highest connected ancestor:
 *	1. while check if chain is connected: (log^2 N)
 *		connected:
 *			chain <- chain_top.parent
 *			continue
 *		else:
 *			break
 *	2. parametric search (log^2 N)
 * 
 * if connection changed on node i:
 *	range update from direct parent of i to highest connected ancestor (log^2 N)
 *	connected: range.update(dp[i])
 *	disconneted: range.update(-dp[i])
 */