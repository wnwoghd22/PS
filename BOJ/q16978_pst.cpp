#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long ll;
const int LEN = 100'001;

int N, M, K, A[LEN];

struct Node {
	int l, r;
	ll v;
} seg_tree[LEN << 5];

int cur = 0, ptr[LEN];
void init(int i, int s, int e) {
	if (s == e) { seg_tree[i].v = A[s]; return; }
	int m = s + e >> 1;
	seg_tree[i].l = ++cur; seg_tree[i].r = ++cur;
	init(seg_tree[i].l, s, m); init(seg_tree[i].r, m + 1, e);
	seg_tree[i].v = seg_tree[seg_tree[i].l].v + seg_tree[seg_tree[i].r].v;
}
void update(int p, int i, int s, int e, int x, int d) {
	if (s == e) { seg_tree[i].v = A[s] = d; return; }
	int m = s + e >> 1;
	if (x <= m) {
		seg_tree[i].l = ++cur; seg_tree[i].r = seg_tree[p].r;
		update(seg_tree[p].l, seg_tree[i].l, s, m, x, d);
	}
	else {
		seg_tree[i].r = ++cur; seg_tree[i].l = seg_tree[p].l;
		update(seg_tree[p].r, seg_tree[i].r, m + 1, e, x, d);
	}
	seg_tree[i].v = seg_tree[seg_tree[i].l].v + seg_tree[seg_tree[i].r].v;
}
ll query(int i, int s, int e, int l, int r) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) return seg_tree[i].v;
	int m = s + e >> 1;
	return query(seg_tree[i].l, s, m, l, r) + query(seg_tree[i].r, m + 1, e, l, r);
}


int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];

	init(0, 1, N);

	std::cin >> M;
	for (int m = 0, q, i, j, k, v; m < M; ++m) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> i >> v;
			++K;
			update(ptr[K - 1], ptr[K] = ++cur, 1, N, i, v);
		}
		if (q == 2) {
			std::cin >> k >> i >> j;
			std::cout << query(ptr[k], 1, N, i, j) << '\n';
		}
	}
}