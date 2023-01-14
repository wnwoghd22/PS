#include <iostream>

const int MAX = 1'000'000;
int N, A, B, C, seg_tree[MAX * 4];

int get_sum(int left, int right, int index = 1, int start = 1, int end = MAX) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return seg_tree[index];
	int mid = (start + end) / 2;
	return get_sum(left, right, index * 2, start, mid) + get_sum(left, right, index * 2 + 1, mid + 1, end);
}

void update(int n, int diff, int index = 1, int start = 1, int end = MAX) {
	if (n > end || n < start) return;
	seg_tree[index] += diff;
	if (start == end) return;
	int mid = (start + end) / 2;
	update(n, diff, index * 2, start, mid);
	update(n, diff, index * 2 + 1, mid + 1, end);
}

int binary_search(const int n) {
	int l = 1, r = MAX, mid, count, result = MAX;
	while (l <= r) {
		mid = (l + r) / 2;
		count = get_sum(1, mid);
		if (count >= n) {
			result = std::min(mid, result);
			r = mid - 1;
		}
		else l = mid + 1;
	}
	update(result, -1);
	return result;
}

int main() {
	std::cin >> N;
	while (N--) {
		std::cin >> A;
		if (A - 1) std::cin >> B >> C, update(B, C);
		else std::cin >> B, std::cout << binary_search(B) << '\n';
	}
}