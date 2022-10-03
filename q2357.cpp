#include <iostream>

const int MAX = 1'000'000;

int N;
int arr[MAX];
int maxSegTree[MAX * 4];
int minSegTree[MAX * 4];

int make_max_seg_tree(int start = 0, int end = N - 1, int index = 1) {
	if (start == end) return maxSegTree[index] = arr[start];
	int mid = (start + end) / 2;
	return maxSegTree[index] = std::max(make_max_seg_tree(start, mid, index * 2), make_max_seg_tree(mid + 1, end, index * 2 + 1));
}

int get_max(int left, int right, int index = 1, int start = 0, int end = N - 1) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return maxSegTree[index];
	int mid = (start + end) / 2;
	return std::max(get_max(left, right, index * 2, start, mid), get_max(left, right, index * 2 + 1, mid + 1, end));
}

int make_min_seg_tree(int start = 0, int end = N - 1, int index = 1) {
	if (start == end) return minSegTree[index] = arr[start];
	int mid = (start + end) / 2;
	return minSegTree[index] = std::min(make_min_seg_tree(start, mid, index * 2), make_min_seg_tree(mid + 1, end, index * 2 + 1));
}

int get_min(int left, int right, int index = 1, int start = 0, int end = N - 1) {
	if (left > end || right < start) return 1'000'000'001;
	if (left <= start && end <= right) return minSegTree[index];
	int mid = (start + end) / 2;
	return std::min(get_min(left, right, index * 2, start, mid), get_min(left, right, index * 2 + 1, mid + 1, end));
}

int main() {
	int M;
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> arr[i];

	make_max_seg_tree();
	make_min_seg_tree();

	while (M--) {
		int a, b;
		std::cin >> a >> b;
		std::cout << get_min(a - 1, b - 1) << ' ' << get_max(a - 1, b - 1) << '\n';
	}
}