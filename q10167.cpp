#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long int ll;
const ll INF = 1e15;
const int LEN = 3'000;
struct SegNode {
	ll lmax, rmax, max, sum;
	const SegNode operator+=(const int& r) {
		lmax = rmax = max = sum += r;
		return *this;
	}
	SegNode operator+(const SegNode& r) const {
		return {
			std::max(lmax, sum + r.lmax),
			std::max(rmax + r.sum, r.rmax),
			std::max({max, r.max, rmax + r.lmax}),
			sum + r.sum
		};
	}
} seg_tree[LEN * 4];
int N, M, A, i, j;

void update(int order, ll diff, int start = 0, int end = N - 1, int index = 1) {
	if (start == end) { seg_tree[index] += diff; return; }
	int mid = (start + end) / 2;
	if (order <= mid) update(order, diff, start, mid, index * 2);
	else update(order, diff, mid + 1, end, index * 2 + 1);
	seg_tree[index] = seg_tree[index * 2] + seg_tree[index * 2 + 1];
}
ll get_max() { return seg_tree[1].max; }

struct Vert {
	int x, y, i, j;
	ll w;
} mines[LEN];
bool CompX(const Vert& l, const Vert& r) { return l.x < r.x; }
bool CompY(const Vert& l, const Vert& r) { return l.y < r.y; }

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> mines[i].x >> mines[i].y >> mines[i].w;

	std::sort(mines, mines + N, CompX);
	for (int i = 1, j = 0; i < N; ++i) {
		if (mines[i].x != mines[i - 1].x) ++j;
		mines[i].i = j;
	}
	std::sort(mines, mines + N, CompY);
	for (int i = 1, j = 0; i < N; ++i) {
		if (mines[i].y != mines[i - 1].y) ++j;
		mines[i].j = j;
	}
	ll result = 0;
	for (int i = 0, k = 0; i < N; ++i, k = 0) {
		memset(seg_tree, 0, sizeof seg_tree);
		while (k < N && mines[k].j < i) ++k;
		for (int j = i; j < N; ++j) {
			while (k < N && mines[k].j == j) {
				update(mines[k].i, mines[k].w);
				++k;
			}
			result = std::max(result, get_max());
		}
	}
	std::cout << result;
}