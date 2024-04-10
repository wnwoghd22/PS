#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 2001;

int P1, P2, C1, C2;
struct Pos { int x, y, i, j, c; } p[LEN];
bool CompX(const Pos& l, const Pos& r) { return l.x < r.x; }
bool CompY(const Pos& l, const Pos& r) { return l.y < r.y; }

struct Node {
	int l, r, max, sum;
	const Node operator+=(const int& d) {
		l = r = max = sum += d;
		return *this;
	}
	Node operator+(const Node& rhs) const {
		return {
			std::max(l, sum + rhs.l),
			std::max(r + rhs.sum, rhs.r),
			std::max({r + rhs.l, max, rhs.max}),
			sum + rhs.sum
		};
	}
} seg_tree[LEN * 4];

void update(int n, int d, int s = 0, int e = LEN, int i = 1) {
	if (e < n || n < s) return;
	if (s == e) { seg_tree[i] += d; return; }
	int m = (s + e) / 2;
	update(n, d, s, m, i << 1), update(n, d, m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] + seg_tree[i << 1 | 1];
}

int query() { return seg_tree[1].max; }

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> P1;
	for (int i = 0; i < P1; ++i) std::cin >> p[i].x >> p[i].y;

	std::cin >> P2;
	for (int i = P1; i < P1 + P2; ++i) std::cin >> p[i].x >> p[i].y;

	std::cin >> C1 >> C2;
	for (int i = 0; i < P1; ++i) p[i].c = C1;
	for (int i = P1; i < P1 + P2; ++i) p[i].c = -C2;

	// compress
	std::sort(p, p + P1 + P2, CompY);
	int x = 0, y = 0;
	for (int i = 1; i < P1 + P2; ++i) {
		if (p[i].y != p[i - 1].y) ++y;
		p[i].j = y;
	}
	std::sort(p, p + P1 + P2, CompX);
	for (int i = 1; i < P1 + P2; ++i) {
		if (p[i].x != p[i - 1].x) ++x;
		p[i].i = x;
	}

	int result = 0;
	for (int i = 0, pivot = 0; i <= x; ++i) {
		memset(seg_tree, 0, sizeof seg_tree);
		while (pivot < P1 + P2 && p[pivot].i < i) ++pivot;
		for (int j = i, k = pivot; j <= x; ++j) {
			while (k < P1 + P2 && p[k].i == j) {
				update(p[k].j, p[k].c);
				++k;
			}
			result = std::max(result, query());
		}
	}
	std::cout << result;
}