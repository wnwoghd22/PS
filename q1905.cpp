#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef long long int ll;
const int LEN = 1001;
ll Lx, Ly, N, lx, ly, lz, px, py, max;
struct MaxSegTree {
	ll seg_tree[LEN * 4];
	void update(int l, int r, ll d, int s = 0, int e = Ly, int i = 1) {
		if (r < s || e < l) return;
		if (l <= s && e <= r) {
			seg_tree[i] = d;
			return;
		}
		int m = (s + e) / 2;
		update(l, r, d, s, m, i << 1);
		update(l, r, d, m + 1, e, i << 1 | 1);
	}
	ll get_max(int l, int r, int s = 0, int e = Ly, int i = 1) {
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) return seg_tree[i];
		int m = (s + e) / 2;
		return std::max({ seg_tree[i], get_max(l, r, s, m, i << 1), get_max(l, r, m + 1, e, i << 1 | 1) });
	}
} seg_tree[LEN];

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> Lx >> Ly >> N;
	while (N--) {
		std::cin >> lx >> ly >> lz >> px >> py;
		max = 0;
		for (int x = 0; x < lx; ++x) max = std::max(max, seg_tree[px + x].get_max(py, py + ly - 1));
		max += lz;
		for (int x = 0; x < lx; ++x) seg_tree[px + x].update(py, py + ly - 1, max);
	}
	for (int x = 0; x < Lx; ++x) max = std::max(max, seg_tree[x].get_max(0, Ly));
	std::cout << max;
}