#include <iostream>
#include <algorithm>

const int LEN = 1'000'001;
const int N_LEN = 100'001;
int seg_max[LEN * 4], lazy[LEN * 4];
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
void update(int l, int r, int d, int s = 0, int e = LEN - 1, int i = 1) {
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

struct Edge {
	int y, l, r, d;
	bool operator<(const Edge& rhs) const {
		if (y == rhs.y) return d > rhs.d;
		return y < rhs.y;
	}
} edges[N_LEN * 2];
int L, R, U, D, E, sp, posY[LEN], Y[N_LEN * 2], X, N, max;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	L = D = 0; U = R = LEN - 1;
	std::cin >> X;
	std::cin >> N;
	for (int i = 0, l, r, u, d; i < N; ++i) {
		std::cin >> l >> d >> r >> u;
		if (r - l > X || u - d > X) continue;
		u = std::max(D, u - X);
		r = std::max(L, r - X);
		d = std::min(U - X, d);
		l = std::min(R - X, l);
		posY[u] = posY[d] = 1;
		edges[E++] = { u, r, l, 1 };
		edges[E++] = { d, r, l, -1 };
	}
	for (int i = D; i <= U; ++i)
		if (posY[i])
			Y[sp++] = i;
	std::sort(edges, edges + E);
	// for (int i = 0; i < E; ++i) std::cout << edges[i].y << ' ' << edges[i].l << ' ' << edges[i].r << ' ' << edges[i].d << '\n';
	for (int i = 0; i < E; ++i) {
		update(edges[i].l, edges[i].r, edges[i].d);
		max = std::max(max, get_max());
	}
	std::cout << max;
}