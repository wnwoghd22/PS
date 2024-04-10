#include <iostream>

typedef long long int ll;
const ll MAX = 1'000'000;

ll N;
ll arr[MAX];
ll segTree[MAX * 4];

ll make_seg_tree(int start = 0, int end = N - 1, int index = 1) {
	if (start == end) return segTree[index] = arr[start];
	int mid = (start + end) / 2;
	return segTree[index] = make_seg_tree(start, mid, index * 2) + make_seg_tree(mid + 1, end, index * 2 + 1);
}

ll get_sum(int left, int right, int index = 1, int start = 0, int end = N - 1) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return segTree[index];
	int mid = (start + end) / 2;
	return get_sum(left, right, index * 2, start, mid) + get_sum(left, right, index * 2 + 1, mid + 1, end);
}

void update(int n, ll diff, int index = 1, int start = 0, int end = N - 1) {
	if (n > end || n < start) return;
	segTree[index] += diff;
	if (start == end) return;
	int mid = (start + end) / 2;
	update(n, diff, index * 2, start, mid);
	update(n, diff, index * 2 + 1, mid + 1, end);
}

int main() {
	int M, K;
	std::cin >> N >> M >> K;
	int query = M + K;
	for (int i = 0; i < N; ++i) std::cin >> arr[i];

	make_seg_tree();

	for (int i = 1; i <= N * 4; ++i) std::cout << segTree[i] << ' ';
	std::cout << '\n';

	while (query--) {
		ll a, b, c;
		std::cin >> a >> b >> c;
		if (a == 1) {
			ll dif = c - arr[b - 1];
			arr[b - 1] = c;
			update(b - 1, dif);
		}
		else std::cout << get_sum(b - 1, c - 1) << '\n';
	}
}