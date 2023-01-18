#include <iostream>
#include <algorithm>

typedef long long int ll;
const ll INF = 1e9;
const int LEN = 100'001;
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

void update(int order, ll diff, int start = 1, int end = N, int index = 1) {
	if (start == end) { seg_tree[index] += diff; return; }
	int mid = (start + end) / 2;
	if (order <= mid) update(order, diff, start, mid, index * 2);
	else update(order, diff, mid + 1, end, index * 2 + 1);
	seg_tree[index] = seg_tree[index * 2] + seg_tree[index * 2 + 1];
}

SegNode get_max(int left, int right, int start = 1, int end = N, int index = 1) {
	if (end < left || right < start) return { -INF, -INF, -INF, -INF };
	if (left <= start && end <= right) return seg_tree[index];
	int mid = (start + end) / 2;
	return get_max(left, right, start, mid, index * 2) + get_max(left, right, mid + 1, end, index * 2 + 1);
}

int main() {
	std::cin >> N;
	for (i = 1; i <= N; ++i) {
		std::cin >> A;
		update(i, A);
	}
	std::cin >> M;
	while (M--) {
		std::cin >> i >> j;
		std::cout << get_max(i, j).max << '\n';
	}
}