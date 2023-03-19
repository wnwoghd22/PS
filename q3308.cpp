#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 1'000'000;
struct Order { 
	int l, r;
	Order() : l(0), r(0) {}
	Order(int l, int r) : l(l), r(r) {}
	bool operator==(const Order& rhs) const { return l == rhs.l && r == rhs.r; }
	bool operator!=(const Order& rhs) const { return l != rhs.l || r != rhs.r; }
	bool operator<(const Order& rhs) const { return l < rhs.l; }
} order[LEN];

int N, M, seg_tree[LEN * 4];
void update(int x, int d, int s = 1, int e = M, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) {
		seg_tree[i] += d;
		return;
	}
	int m = s + e >> 1;
	update(x, d, s, m, i << 1);
	update(x, d, m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] + seg_tree[i << 1 | 1];
}
int get(int l, int r, int s = 1, int e = M, int i = 1) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) return seg_tree[i];
	int m = s + e >> 1;
	return get(l, r, s, m, i << 1) + get(l, r, m + 1, e, i << 1 | 1);
}
Order get_order(int x) { return { get(1, x - 1), get(x + 1, M) }; }

int fail[LEN];
void get_fail(int* p) {
	memset(seg_tree, 0, sizeof seg_tree);
	for (int i = 0; p[i]; ++i) {
		update(p[i], 1);
		order[i] = get_order(p[i]);
	}
	memset(seg_tree, 0, sizeof seg_tree);
	for (int i = 1, j = 0; p[i]; ++i) {
		while (j && order[j] != get_order(p[i])) {
			for (int k = i - j; k < i - fail[j - 1]; ++k) update(p[k], -1);
			j = fail[j - 1];
		}
		if (order[j] == get_order(p[i])) {
			update(p[i], 1);
			fail[i] = ++j;
		}
	}
}

int sp, stack[LEN];
int kmp(int* p, int* t) {
	get_fail(p);
	memset(seg_tree, 0, sizeof seg_tree);
	for (int i = 0, j = 0; t[i]; ++i) {
		while (j && order[j] != get_order(t[i])) {
			for (int k = i - j; k < i - fail[j - 1]; ++k) update(t[k], -1);
			j = fail[j - 1];
		}
		if (order[j] == get_order(t[i])) {
			if (j == N - 1) {
				stack[sp++] = i - j + 1;
				for (int k = i - j; k < i - fail[j] + 1; ++k) update(t[k], -1);
				j = fail[j];
			}
			else ++j;
			update(t[i], 1);
		}
	}
	return sp;
}

int P[LEN], T[LEN];
int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	for (int i = 1, j; i <= N; P[j - 1] = i++) std::cin >> j;
	for (int i = 0; i < M; order[i].r = i++) std::cin >> order[i].l;
	std::sort(order, order + M);
	for (int i = 0; i < M; ++i) T[order[i].r] = i + 1;

	/*for (int i = 0; i < N; ++i)
		std::cout << P[i] << ' ';
	std::cout << '\n';
	for (int i = 0; i < M; ++i)
		std::cout << T[i] << ' ';
	std::cout << '\n';*/
	
	std::cout << kmp(P, T) << '\n';
	for (int i = 0; i < sp; ++i)
		std::cout << stack[i] << ' ';
	std::cout << '\n';
}