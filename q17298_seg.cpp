#include <iostream>

const int LEN = 1'000'002;

int N, A[LEN];

int seg_max[LEN << 2];
void update(int x, int d, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) { seg_max[i] = d; return; }
	int m = s + e >> 1;
	update(x, d, s, m, i << 1);
	update(x, d, m + 1, e, i << 1 | 1);
	seg_max[i] = std::max(seg_max[i << 1], seg_max[i << 1 | 1]);
}
int get_max(int l, int r, int s = 1, int e = N, int i = 1) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) { return seg_max[i]; }
	int m = s + e >> 1;
	return std::max(get_max(l, r, s, m, i << 1), get_max(l, r, m + 1, e, i << 1 | 1));
}

int get_rightmost(int i) {
	int l = i + 1, r = N, m, j = N + 1;
	while (l <= r) {
		m = l + r >> 1;
		if (get_max(i + 1, m) > A[i]) {
			j = std::min(m, j);
			r = m - 1;
		}
		else l = m + 1;
	}
	return j;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		update(i, A[i]);
	}
	A[N + 1] = -1;
	for (int i = 1; i <= N; ++i) {
		int j = get_rightmost(i);
		std::cout << A[j] << ' ';
	}
}