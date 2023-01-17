#include <iostream>

const int LEN = 500'000;
int mod_len[LEN], seg_tree[LEN * 4];
int N, k, d, S, result, max;

int get_max(int left, int right, int index = 1, int start = 0, int end = LEN) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return seg_tree[index];
	int mid = (start + end) / 2;
	return std::max(get_max(left, right, index * 2, start, mid), get_max(left, right, index * 2 + 1, mid + 1, end));
}

int update_max(int n, int k, int start = 0, int end = LEN, int index = 1) {
	if (n > end || n < start) return seg_tree[index];
	if (start == end) return seg_tree[index] = k;
	int mid = (start + end) / 2;
	return seg_tree[index] = std::max(update_max(n, k, start, mid, index * 2), update_max(n, k, mid + 1, end, index * 2 + 1));
}

int main() {
	std::cin >> N >> k >> d;
	while (N--) {
		std::cin >> S;
		max = std::max(mod_len[S % k], get_max(S - d, S + d)) + 1;
		result = std::max(result, max);
		mod_len[S % k] = max;
		update_max(S, max);
	}
	std::cout << result;
}