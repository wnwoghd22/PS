#include <iostream>
#include <algorithm>

const int LEN = 2'000'000;
const int INF = 1e9;
int N, K;

struct Node {
	int low, up;
	Node operator&(const Node& r) {
		return { std::min(std::max(low, r.low), r.up), std::min(std::max(up, r.low), r.up) };
	}
} seg_tree[LEN * 4];

void update(int left, int right, Node n, int index = 1, int start = 0, int end = N - 1) {
	if (left > end || right < start) return;

	if (start != end) {
		seg_tree[index * 2] = seg_tree[index * 2] & seg_tree[index];
		seg_tree[index * 2 + 1] = seg_tree[index * 2 + 1] & seg_tree[index];
		seg_tree[index] = { 0, INF };
	}

	if (left <= start && end <= right) {
		seg_tree[index] = seg_tree[index] & n;
		return;
	}
	int mid = (start + end) / 2;
	update(left, right, n, index * 2, start, mid);
	update(left, right, n, index * 2 + 1, mid + 1, end);
}
Node get_diff(int i, int start = 0, int end = N - 1, int index = 1) {
	if (i > end || i < start) return { 0, INF };
	if (start == end) return seg_tree[index];

	int mid = (start + end) / 2;
	return get_diff(i, start, mid, index * 2) & get_diff(i, mid + 1, end, index * 2 + 1) & seg_tree[index];
}

int main() {
	int op, l, r, h;
	std::cin >> N >> K;
	while (K--) {
		std::cin >> op >> l >> r >> h;
		if (op == 1) update(l, r, { h, INF });
		else update(l, r, { 0, h });
	}
	for (int i = 0; i < N; ++i)
		std::cout << get_diff(i).up << '\n';
}