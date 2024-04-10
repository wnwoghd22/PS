#include <iostream>

const int MAX = 500'000;

int N, M;
int segTree[MAX * 4];
int lazy[MAX * 4];

void propagate(int index, int start, int end) {
	if (lazy[index]) {
		segTree[index] ^= (start - end + 1) & 1 ? lazy[index] : 0;
		if (start != end) {
			lazy[index * 2] ^= lazy[index];
			lazy[index * 2 + 1] ^= lazy[index];
		}
		lazy[index] = 0;
	}
}

void update_diff(int left, int right, int diff, int index = 1, int start = 0, int end = N - 1) {
	propagate(index, start, end);

	if (left > end || right < start) return;
	if (left <= start && end <= right) {
		segTree[index] ^= (start - end + 1) & 1 ? diff : 0;
		if (start != end) {
			lazy[index * 2] ^= diff;
			lazy[index * 2 + 1] ^= diff;
		}
		return;
	}
	int mid = (start + end) / 2;
	update_diff(left, right, diff, index * 2, start, mid);
	update_diff(left, right, diff, index * 2 + 1, mid + 1, end);

	segTree[index] = segTree[index * 2] ^ segTree[index * 2 + 1];
}

int get_diff(int left, int right, int start = 0, int end = N - 1, int index = 1) {
	propagate(index, start, end);

	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return segTree[index];

	int mid = (start + end) / 2;
	return get_diff(left, right, start, mid, index * 2) ^ get_diff(left, right, mid + 1, end, index * 2 + 1);
}

int main() {
	int Q, i, j, k;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> j;
		update_diff(i, i, j);
	}
	std::cin >> M;
	while (M--) {
		std::cin >> Q;
		if (Q == 1) {
			std::cin >> i >> j >> k;
			update_diff(i, j, k);
		}
		if (Q == 2) {
			std::cin >> i >> j;
			std::cout << get_diff(i, j) << '\n';
		}
	}
}