#include <iostream>
#include <algorithm>

typedef long long int ll;
const ll MOD = 1e9 + 7;
const int MAX = 100'000;

int N, M;
ll seg_tree[MAX * 4], lazy_add[MAX * 4], lazy_mul[MAX * 4];

void propagate(int index, int start, int end) {
	if (lazy_mul[index] != 1 || lazy_add[index]) {
		ll mul = lazy_mul[index], add = lazy_add[index];
		seg_tree[index] = (mul * seg_tree[index] % MOD + add * (end - start + 1)) % MOD;
		if (start != end) {
			for (int i = index * 2; i <= index * 2 + 1; ++i) {
				ll mul2 = lazy_mul[i], add2 = lazy_add[i];
				lazy_mul[i] = mul * mul2 % MOD;
				lazy_add[i] = (mul * add2 + add) % MOD;
			}
		}
		lazy_add[index] = 0;
		lazy_mul[index] = 1;
	}
}

void update(int left, int right, ll mul, ll add, int index = 1, int start = 1, int end = N) {
	propagate(index, start, end);

	if (left > end || right < start) return;
	if (left <= start && end <= right) {
		seg_tree[index] *= mul; seg_tree[index] %= MOD;
		seg_tree[index] += add * (end - start + 1); seg_tree[index] %= MOD;
		if (start != end) {
			for (int i = index * 2; i <= index * 2 + 1; ++i) {
				ll mul2 = lazy_mul[i], add2 = lazy_add[i];
				lazy_mul[i] = mul * mul2 % MOD;
				lazy_add[i] = (mul * add2 + add) % MOD;
			}
		}
		return;
	}
	int mid = (start + end) / 2;
	update(left, right, mul, add, index * 2, start, mid);
	update(left, right, mul, add, index * 2 + 1, mid + 1, end);

	seg_tree[index] = (seg_tree[index * 2] + seg_tree[index * 2 + 1]) % MOD;
}
ll get_diff(int left, int right, int start = 1, int end = N, int index = 1) {
	propagate(index, start, end);

	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return seg_tree[index];

	int mid = (start + end) / 2;
	return (get_diff(left, right, start, mid, index * 2) + get_diff(left, right, mid + 1, end, index * 2 + 1)) % MOD;
}

int main() {
	std::fill(lazy_mul, lazy_mul + MAX, 1);
	ll q, x, y, v;
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> x;
		update(i, i, 1, x);
	}
	std::cin >> M;
	while (M--) {
		std::cin >> q >> x >> y;
		if (q == 1) {
			std::cin >> v;
			update(x, y, 1, v);
		}
		if (q == 2) {
			std::cin >> v;
			update(x, y, v, 0);
		}
		if (q == 3) {
			std::cin >> v;
			update(x, y, 0, v);
		}
		if (q == 4) std::cout << get_diff(x, y) << '\n';
	}
}