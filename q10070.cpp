#include <iostream>
#include <algorithm>

const int LEN = 2'000'000;
const int MAX = 100'001;
int N, K;
int seg_tree[LEN * 4], lazy_min[LEN * 4], lazy_max[LEN * 4];
void add(int left, int right, int max, int index = 1, int start = 0, int end = N - 1);
void sub(int left, int right, int min, int index = 1, int start = 0, int end = N - 1);

void propagate(int index, int start, int end) {
	if (lazy_min[index] != MAX) {
		int current = seg_tree[index], min = lazy_min[index];
		seg_tree[index] = std::min(min, current);
		if (start != end) {
			for (int i = index * 2; i <= index * 2 + 1; ++i) {
				lazy_min[i] = std::min(min, lazy_min[i]);
				lazy_max[i] = -1;
			}
		}
	}
	if (~lazy_max[index]) {
		int current = seg_tree[index], max = lazy_max[index];
		seg_tree[index] = std::max(max, current);
		if (start != end) {
			for (int i = index * 2; i <= index * 2 + 1; ++i) {
				lazy_min[i] = MAX;
				lazy_max[i] = std::max(max, lazy_max[i]);
			}
		}
	}
	lazy_min[index] = MAX;
	lazy_max[index] = -1;
}

void add(int left, int right, int max, int index, int start, int end) {
	propagate(index, start, end);

	if (left > end || right < start) return;

	int current = seg_tree[index];
	if (left <= start && end <= right) {
		seg_tree[index] = std::max(current, max);
		if (start != end) {
			for (int i = index * 2; i <= index * 2 + 1; ++i) {
				lazy_min[i] = MAX;
				lazy_max[i] = std::max(max, lazy_max[i]);
			}
		}
		lazy_min[index] = MAX;
		lazy_max[index] = -1;
		return;
	}
	int mid = (start + end) / 2;
	add(left, right, max, index * 2, start, mid);
	add(left, right, max, index * 2 + 1, mid + 1, end);

	seg_tree[index] = std::min(seg_tree[index * 2], seg_tree[index * 2 + 1]);
}
void sub(int left, int right, int min, int index, int start, int end) {
	propagate(index, start, end);

	if (left > end || right < start) return;

	int current = seg_tree[index];
	if (left <= start && end <= right) {
		seg_tree[index] = std::min(current, min);
		if (start != end) {
			for (int i = index * 2; i <= index * 2 + 1; ++i) {
				lazy_min[i] = std::min(min, lazy_min[i]);
				lazy_max[i] = -1;
			}
		}
		lazy_min[index] = MAX;
		lazy_max[index] = -1;
		return;
	}
	int mid = (start + end) / 2;
	sub(left, right, min, index * 2, start, mid);
	sub(left, right, min, index * 2 + 1, mid + 1, end);

	seg_tree[index] = std::min(seg_tree[index * 2], seg_tree[index * 2 + 1]);
}

int get_diff(int i, int start = 0, int end = N - 1, int index = 1) {
	propagate(index, start, end);

	if (i > end || i < start) return 0;
	if (start == end) return seg_tree[index];

	int mid = (start + end) / 2;
	return std::max({ seg_tree[index], get_diff(i, start, mid, index * 2), get_diff(i, mid + 1, end, index * 2 + 1) });
}

int main() {
	for (int i = 0; i < LEN * 4; ++i) lazy_max[i] = -1, lazy_min[i] = MAX;
	int op, l, r, h;
	std::cin >> N >> K;
	while (K--) {
		std::cin >> op >> l >> r >> h;
		if (op == 1) add(l, r, h);
		else sub(l, r, h);
	}
	for (int i = 0; i < N; ++i)
		std::cout << get_diff(i) << '\n';
}