#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int LEN = 100'001;
const int INF = 2e9;

int N, M, A[LEN], v[LEN], len, c[LEN], o[LEN]; // value, compressed, order

void merge(int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) c[k++] = A[o[i]] <= A[o[j]] ? o[i++] : o[j++];
	while (i <= m) c[k++] = o[i++];
	while (j <= r) c[k++] = o[j++];
	for (i = l; i <= r; ++i) o[i] = c[i];
}
void merge_sort(int l, int r) {
	if (l < r) {
		int m = l + r >> 1;
		merge_sort(l, m);
		merge_sort(m + 1, r);
		merge(l, m, r);
	}
}

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
	if (s == e) { seg_tree[i].v += d; return; }
	int m = s + e >> 1;
	if (x <= m) { // update left
		seg_tree[i].l = ++cur; seg_tree[i].r = seg_tree[p].r;
		update(seg_tree[p].l, seg_tree[i].l, s, m, x, d);
	}
	else {
		seg_tree[i].r = ++cur; seg_tree[i].l = seg_tree[p].l;
		update(seg_tree[p].r, seg_tree[i].r, m + 1, e, x, d);
	}
	seg_tree[i].v = seg_tree[seg_tree[i].l].v + seg_tree[seg_tree[i].r].v;
}

int query(int l, int r, int s, int e, int k) {
	if (s == e) return s;
	int m = s + e >> 1;
	int d = seg_tree[seg_tree[r].l].v - seg_tree[seg_tree[l].l].v;
	if (d >= k) return query(seg_tree[l].l, seg_tree[r].l, s, m, k);
	else return query(seg_tree[l].r, seg_tree[r].r, m + 1, e, k - d);
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> A[i], o[i] = i;
	merge_sort(0, N - 1);
	for (int i = 0, j = -INF; i < N; ++i) {
		if (A[o[i]] ^ j)
			v[len++] = j = A[o[i]];
		c[o[i]] = len - 1;
	}
	// for (int i = 0; i < N; ++i) std::cout << c[i] << ' ';

	init(0, 0, N - 1);
	for (int i = 1; i <= N; ++i)
		update(ptr[i - 1], ptr[i] = ++cur, 0, N - 1, c[i - 1], 1);
	// for (int i = 0; i <= N; ++i) std::cout << ptr[i] << '\n';
	
	for (int m = 0, i, j, k; m < M; ++m) {
		std::cin >> i >> j >> k;
		std::cout << v[query(ptr[i - 1], ptr[j], 0, N - 1, k)] << '\n';
	}
}