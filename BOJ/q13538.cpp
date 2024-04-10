#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int LEN = 1 << 19;
const int INF = 2e9;

int N, M;

struct Node {
	int l, r, v;
} seg_tree[LEN << 5];

int cur = 0, ptr[LEN];
void init(int i, int s, int e) {
	if (s == e) return;
	int m = s + e >> 1;
	seg_tree[i].l = ++cur; seg_tree[i].r = ++cur;
	init(seg_tree[i].l, s, m); init(seg_tree[i].r, m + 1, e);
}
void update(int p, int i, int s, int e, int x, int d) {
	if (s == e) { seg_tree[i].v = seg_tree[p].v + d; return; }
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
int query2(int l, int r, int s, int e, int k, int b = 18) {
	if (s == e) return s;
	int m = s + e >> 1;
	if (k & 1 << b) {
		int d = seg_tree[seg_tree[r].l].v - seg_tree[seg_tree[l].l].v;
		if (d) return query2(seg_tree[l].l, seg_tree[r].l, s, m, k, b - 1);
		else return query2(seg_tree[l].r, seg_tree[r].r, m + 1, e, k, b - 1);
	}
	int d = seg_tree[seg_tree[r].r].v - seg_tree[seg_tree[l].r].v;
	if (!d) return query2(seg_tree[l].l, seg_tree[r].l, s, m, k, b - 1);
	else return query2(seg_tree[l].r, seg_tree[r].r, m + 1, e, k, b - 1);
}
int query4(int l, int r, int s, int e, int k) {
	if (s > k) return 0;
	if (e <= k) return seg_tree[r].v - seg_tree[l].v;
	int m = s + e >> 1;
	return query4(seg_tree[l].l, seg_tree[r].l, s, m, k) + query4(seg_tree[l].r, seg_tree[r].r, m + 1, e, k);
}
int query5(int l, int r, int s, int e, int k) {
	if (s == e) return s;
	int m = s + e >> 1;
	int d = seg_tree[seg_tree[r].l].v - seg_tree[seg_tree[l].l].v;
	if (d >= k) return query5(seg_tree[l].l, seg_tree[r].l, s, m, k);
	else return query5(seg_tree[l].r, seg_tree[r].r, m + 1, e, k - d);
}

int main() {
	freopen("input.txt", "r", stdin);
	init(0, 0, LEN - 1);

	std::cin >> M;
	
	for (int m = 0, q, l, r, k; m < M; ++m) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> k; ++N;
			update(ptr[N - 1], ptr[N] = ++cur, 0, LEN - 1, k, 1);
		}
		if (q == 2) {
			std::cin >> l >> r >> k;
			std::cout << query2(ptr[l - 1], ptr[r], 0, LEN - 1, k) << '\n';
		}
		if (q == 3) {
			std::cin >> k;
			cur = ptr[(N -= k) + 1] - 1;
		}
		if (q == 4) {
			std::cin >> l >> r >> k;
			std::cout << query4(ptr[l - 1], ptr[r], 0, LEN - 1, k) << '\n';
		}
		if (q == 5) {
			std::cin >> l >> r >> k;
			std::cout << query5(ptr[l - 1], ptr[r], 0, LEN - 1, k) << '\n';
		}
	}
}