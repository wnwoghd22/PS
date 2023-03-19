#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 1'000'001;
struct Order {
	int l, r;
	Order() : l(0), r(0) {}
	Order(int l, int r) : l(l), r(r) {}
	bool operator==(const Order& rhs) const { return l == rhs.l && r == rhs.r; }
	bool operator!=(const Order& rhs) const { return l != rhs.l || r != rhs.r; }
	bool operator<(const Order& rhs) const { return l < rhs.l; }
} order[LEN];

int N, M, seg_tree[LEN * 2];
int get(int l, int r) {
	int ans = 0;
	for (l += M, r += M; l < r; l >>= 1, r >>= 1) {
		if (l & 1) ans += seg_tree[l++];
		if (r & 1) ans += seg_tree[--r];
	}
	return ans;
}
void update(int pos, int val) {
	seg_tree[pos + M] += val;
	for (pos += M; pos > 1; pos >>= 1)
		seg_tree[pos >> 1] = seg_tree[pos] + seg_tree[pos ^ 1];
}
Order get_order(int x) { return { get(0, x), get(x + 1, M) }; }

int fail[LEN];
void get_fail(int* p) {
	memset(seg_tree, 0, sizeof seg_tree);
	for (int i = 0; i < N; ++i) {
		update(p[i], 1);
		order[i] = get_order(p[i]);
	}
	memset(seg_tree, 0, sizeof seg_tree);
	for (int i = 1, j = 0; i < N; ++i) {
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
	for (int i = 0, j = 0; i < M; ++i) {
		while (j && order[j] != get_order(t[i])) {
			for (int k = i - j; k < i - fail[j - 1]; ++k) update(t[k], -1);
			j = fail[j - 1];
		}
		if (order[j] == get_order(t[i])) {
			if (j == N - 1) {
				stack[sp++] = i - j + 1;
				for (int k = i - j; k <= i - fail[j]; ++k) update(t[k], -1);
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
	// freopen("input.txt", "r", stdin);
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N >> M;
	for (int i = 0, j; i < N; P[j - 1] = i++) std::cin >> j;
	for (int i = 0; i < M; order[i].r = i, ++i) std::cin >> order[i].l;
	std::sort(order, order + M);
	for (int i = 0; i < M; ++i) T[order[i].r] = i;

	std::cout << kmp(P, T) << '\n';
	for (int i = 0; i < sp; ++i)
		std::cout << stack[i] << ' ';
	std::cout << '\n';
}