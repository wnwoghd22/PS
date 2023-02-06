#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long int ll;
const int LEN = 1'000'001;
ll seg_tree[LEN * 2];
int N, order[LEN];

void update(int n, ll d, int s = 0, int e = N - 1, int i = 1) {
	if (e < n || n < s) return;
	seg_tree[i] += d;
	if (s == e) return;
	int m = (s + e) / 2;
	update(n, d, s, m, i << 1);
	update(n, d, m + 1, e, i << 1 | 1);
}
ll get_sum(int l, int r, int s = 0, int e = N - 1, int i = 1) {
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) return seg_tree[i];
	int m = (s + e) / 2;
	return get_sum(l, r, s, m, i << 1) + get_sum(l, r, m + 1, e, i << 1 | 1);
}

int main() {
	freopen("input.txt", "r", stdin);

	ll result = 0;
	std::cin >> N;
	for (int i = 0, a; i < N; ++i) std::cin >> a, order[a] = i;
	for (int i = 0, b; i < N; ++i) std::cin >> b, result += get_sum(order[b] + 1, N - 1), update(order[b], 1);
	std::cout << result;
}