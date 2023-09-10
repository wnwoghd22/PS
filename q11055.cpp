#include <iostream>
#include <algorithm>

const int LEN = 1000;
int N, A, t[LEN << 2];

void update(int x, int d, int s = 0, int e = LEN, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) { t[i] = d; return; }
	int m = s + e >> 1;
	update(x, d, s, m, i << 1); update(x, d, m + 1, e, i << 1 | 1);
	t[i] = std::max(t[i << 1], t[i << 1 | 1]);
}
int get(int l, int r, int s = 0, int e = LEN, int i = 1) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) return t[i];
	int m = s + e >> 1;
	return std::max(get(l, r, s, m, i << 1), get(l, r, m + 1, e, i << 1 | 1));
}

int main() {
	std::cin >> N;
	while (N--) {
		std::cin >> A;
		update(A, get(0, A - 1) + A);
	}
	std::cout << get(0, LEN);
}