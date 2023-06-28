#include <iostream>
#include <algorithm>
#include <vector>

const int LEN = 500'001;

int N, U, D, S;

struct SegTree {
	int t[LEN << 2];
	void update(int x, int d, int s = 0, int e = LEN, int i = 0) {

	}
	int get_max(int l, int r, int s = 0, int e = LEN, int i = 0) {

	}
} seg_u, seg_d;

struct Market {
	int l, m;
	bool operator<(const Market& r) const { return l < r.l; }
};
std::vector<Market> markets[LEN];

