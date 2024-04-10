#include <iostream>
#include <algorithm>

const int LEN = 1e6;

int N, M, A[LEN];
int c[LEN], t[LEN << 2];
void update(int x, int d, int s = 0, int e = LEN, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) {
		t[i] = x * !!(c[x] += d);
		return;
	}
	int m = s + e >> 1;
	update(x, d, s, m, i << 1); update(x, d, m + 1, e, i << 1 | 1);
	t[i] = std::max(t[i << 1], t[i << 1 | 1]);
}
int get_max() { return t[1]; }

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	for (int i = 0; i < std::min(M * 2 - 1, N); ++i) update(A[i], 1);
	for (int i = M * 2 - 2; i < N; ++i) {
		update(A[i], 1);
		std::cout << get_max() << ' ';
		update(A[i - M * 2], -1);
	}
}