#include <iostream>

typedef long long int ll;
const int MAX = 100'000;

int N, Q;
ll arr[MAX];
ll seg_range[MAX * 4], seg_count[MAX * 4];

void update(int left, int right, int index = 1, int start = 1, int end = N) {
	if (left > end || right < start) return;
	if (start == end || left <= start && end <= right) {
		++seg_count[index];
		seg_range[index] += start - left + 1; return;
	}
	int mid = (start + end) / 2;
	update(left, right, index * 2, start, mid);
	update(left, right, index * 2 + 1, mid + 1, end);
}

ll get(int n, int start = 1, int end = N, int index = 1) {
	if (n > end || n < start) return 0;
	if (start == end) return seg_range[index] + arr[n];
	int mid = (start + end) / 2;
	ll interval = n - start;
	int count = seg_range[index] + seg_count[index] * interval;
	return count + get(n, start, mid, index * 2) + get(n, mid + 1, end, index * 2 + 1);
}

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> arr[i];

	std::cin >> Q;
	while (Q--) {
		ll q, x, l, r;
		std::cin >> q;
		if (q == 1) {
			std::cin >> l >> r;
			update(l, r);
		}
		if (q == 2) {
			std::cin >> x;
			std::cout << get(x) << '\n';
		}
	}
}