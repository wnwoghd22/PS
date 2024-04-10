#include <iostream>

typedef long long int ll;
const int MAX = 1'000'000;

int N;
ll arr[MAX];
ll segTree[MAX * 4];

void update_diff(int left, int right, ll diff, int index = 1, int start = 0, int end = N - 1) {
	if (left > end || right < start) return;
	if (start == end || left <= start && end <= right) {
		segTree[index] += diff; return;
	}
	int mid = (start + end) / 2;
	update_diff(left, right, diff, index * 2, start, mid);
	update_diff(left, right, diff, index * 2 + 1, mid + 1, end);
}

ll get_diff(int n, int start = 0, int end = N - 1, int index = 1) {
	if (n > end || n < start) return 0;
	if (start == end) return segTree[index] + arr[n];
	int mid = (start + end) / 2;
	return segTree[index] + get_diff(n, start, mid, index * 2) + get_diff(n, mid + 1, end, index * 2 + 1);
}

int main() {
	int M;
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> arr[i];

	std::cin >> M;
	while (M--) {
		ll q, a, b, c;
		std::cin >> q;
		if (q == 1) {
			std::cin >> a >> b >> c;
			update_diff(a - 1, b - 1, c);
			for (int i = 1; i < N * 4; ++i) std::cout << segTree[i] << ' ';
			std::cout << '\n';
		}
		if (q == 2) {
			std::cin >> a;
			std::cout << get_diff(a - 1) << '\n';
		}
	}
}