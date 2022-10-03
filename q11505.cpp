#include <iostream>

typedef long long int ll;
const ll MAX = 1'000'000;
const ll MOD = 1'000'000'007;

ll N;
ll arr[MAX];
ll segTree[MAX * 4];

ll make_seg_tree(int start = 0, int end = N - 1, int index = 1) {
	if (start == end) return segTree[index] = arr[start];
	int mid = (start + end) / 2;
	return segTree[index] = make_seg_tree(start, mid, index * 2) * make_seg_tree(mid + 1, end, index * 2 + 1) % MOD;
}

ll get_mul(int left, int right, int index = 1, int start = 0, int end = N - 1) {
	if (left > end || right < start) return 1;
	if (left <= start && end <= right) return segTree[index];
	int mid = (start + end) / 2;
	return get_mul(left, right, index * 2, start, mid) * get_mul(left, right, index * 2 + 1, mid + 1, end) % MOD;
}

ll update(int n, ll diff, int index = 1, int start = 0, int end = N - 1) {
	if (n > end || n < start) return segTree[index];
	if (start == end) return segTree[index] = arr[n] = diff;
	int mid = (start + end) / 2;
	return segTree[index] = update(n, diff, index * 2, start, mid) * update(n, diff, index * 2 + 1, mid + 1, end) % MOD;
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
		if (a == 1) update(b - 1, c);
		else std::cout << get_mul(b - 1, c - 1) << '\n';
	}
}