#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

/// https://www.shuizilong.com/house/archives/poi-2006-tet-tetris-3d/

const int LEN = 1024;

struct SegTree {
	int t[LEN << 1], z[LEN << 1];
	void update(int, int, int);
	void query(int, int, int);
};

struct SegTree2D {
	SegTree t[LEN << 1], z[LEN << 1];
	void update(int, int, int);
	void query(int, int, int);
} t;

int root = 1;
int xl, xr, yl, yr, h;
int W, H, Q;
int lx, ly, lz, px, py;

void SegTree::update(int i, int l, int r) {
	t[i] = std::max(t[i], h);

	if (yl <= l && r <= yr) {
		z[i] = std::max(z[i], h);
		return;
	}
	int m = l + r >> 1; i <<= 1;
	if (yl <= m) update(i, l, m);
	if (m < yr) update(i | 1, m + 1, r);
}
void SegTree::query(int i, int l, int r) {
	if (yl <= l && r <= yr) {
		h = std::max(h, t[i]);
		return;
	}
	h = std::max(h, z[i]);
	int m = l + r >> 1; i <<= 1;
	if (yl <= m) query(i, l, m);
	if (m < yr) query(i | 1, m + 1, r);
}

void SegTree2D::update(int i, int l, int r) {
	t[i].update(root, 0, H);

	if (xl <= l && r <= xr) {
		z[i].update(root, 0, H);
		return;
	}
	int m = l + r >> 1; i <<= 1;
	if (xl <= m) update(i, l, m);
	if (m < xr) update(i | 1, m + 1, r);
}
void SegTree2D::query(int i, int l, int r) {
	if (xl <= l && r <= xr) {
		t[i].query(root, 0, H);
		return;
	}
	z[i].query(root, 0, H);
	int m = l + r >> 1; i <<= 1;
	if (xl <= m) query(i, l, m);
	if (m < xr) query(i | 1, m + 1, r);
}

int main() {
	// freopen("input.txt", "r", stdin);
	// std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> W >> H >> Q;
	W--; H--;
	while (Q--) {
		std::cin >> lx >> ly >> lz >> px >> py;
		xl = px, xr = lx + px - 1;
		yl = py, yr = ly + py - 1;
		h = 0;
		t.query(root, 0, W);
		h += lz;
		t.update(root, 0, W);
	}
	xl = 0, xr = W;
	yl = 0, yr = H;
	t.query(root, 0, W);
	std::cout << h;
}