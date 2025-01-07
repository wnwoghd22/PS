#include <iostream>

const int LEN = 200'000;
int N, w[LEN], t[LEN * 4];

void update(int x, int d, int s = 1, int e = LEN, int i = 1) {
	if (x < s || e < x) return;
	t[i] += d;
	if (s == e) return;
	int m = s + e >> 1;
	update(x, d, s, m, i << 1);
	update(x, d, m + 1, e, i << 1 | 1);
}

int get_bound(int k, int s = 1, int e = LEN, int i = 1) {
	if (s == e) return s;
	int m = s + e >> 1;
	if (t[i << 1] >= k) return get_bound(k, s, m, i << 1);
	return get_bound(k - t[i << 1], m + 1, e, i << 1 | 1);
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> w[i];
		update(i, w[i]);
	}
	for (int i = 1, k, p; i <= N; ++i) {
		std::cin >> p;
		std::cout << (k = get_bound(p)) << ' ';
		update(k, -w[k]);
	}
}