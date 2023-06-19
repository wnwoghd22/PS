#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long int ll;
const int LEN = 500'000;
ll seg_tree[LEN << 2];
ll N, M, q, i, x;

void update(int n, ll d, int s = 1, int e = N, int i = 1) {
	if (n < s || e < n) return;
	if (s == e) {
		seg_tree[i] += d;
		return;
	}
	int m = (s + e) / 2;
	update(n, d, s, m, i << 1);
	update(n, d, m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] + seg_tree[i << 1 | 1];
}
ll get(int l, int r, int s = 1, int e = N, int i = 1) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) return seg_tree[i];
	int m = (s + e) / 2;
	return get(l, r, s, m, i << 1) + get(l, r, m + 1, e, i << 1 | 1);
}
int binary_search(ll x) {
	int l = 1, r = N, m, result = N;
	while (l <= r) {
		m = (l + r) / 2;
		if (get(1, m) >= x) {
			result = std::min(m, result);
			r = m - 1;
		}
		else l = m + 1;
	}
	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (i = 1; i <= N; ++i) {
		std::cin >> x;
		update(i, x);
	}
	std::cin >> M;
	while (M--) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> i >> x;
			update(i, x);
		}
		if (q == 2) {
			std::cin >> x;
			std::cout << binary_search(x) << '\n';
		}
	}
}