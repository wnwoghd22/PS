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

int update_max(int n, int start = 0, int end = N - 1, int index = 1) {
	if (n > end || n < start) return maxSegTree[index];
	if (start == end) return maxSegTree[index] = arr[n];
	int mid = (start + end) / 2;
	return maxSegTree[index] = std::max(update_max(n, start, mid, index * 2), update_max(n, mid + 1, end, index * 2 + 1));
}

int make_min_seg_tree(int start = 0, int end = N - 1, int index = 1) {
	if (start == end) return minSegTree[index] = arr[start];
	int mid = (start + end) / 2;
	return minSegTree[index] = std::min(make_min_seg_tree(start, mid, index * 2), make_min_seg_tree(mid + 1, end, index * 2 + 1));
}

int get_min(int left, int right, int index = 1, int start = 0, int end = N - 1) {
	if (left > end || right < start) return 1e9;
	if (left <= start && end <= right) return minSegTree[index];
	int mid = (start + end) / 2;
	return std::min(get_min(left, right, index * 2, start, mid), get_min(left, right, index * 2 + 1, mid + 1, end));
}

int update_min(int n, int start = 0, int end = N - 1, int index = 1) {
	if (n > end || n < start) return minSegTree[index];
	if (start == end) return minSegTree[index] = arr[n];
	int mid = (start + end) / 2;
	return minSegTree[index] = std::min(update_min(n, start, mid, index * 2), update_min(n, mid + 1, end, index * 2 + 1));
}

bool check(int a, int b) {
	int max = get_max(a, b);
	int min = get_min(a, b);
	return min == a && max == b;
}

void swap(int a, int b) {
	int temp = arr[a]; arr[a] = arr[b]; arr[b] = temp;
	update_max(a); update_max(b);
	update_min(a); update_min(b);
}

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int K;
		std::cin >> N >> K;
		for (int i = 0; i < N; ++i) arr[i] = i;

		make_max_seg_tree();
		make_min_seg_tree();

		while (K--) {
			int q, a, b;
			std::cin >> q >> a >> b;
			if (q == 0) swap(a, b);
			if (q == 1) std::cout << (check(a, b) ? "YES" : "NO") << '\n';
		}
	}
}