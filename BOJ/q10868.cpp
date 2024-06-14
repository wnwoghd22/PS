#include <iostream>

const int LEN = 100'001;

int N, M, A[LEN], t[LEN << 2];

void init(int s = 1, int e = N, int i = 1) {
	if (s == e) { t[i] = A[s]; return; }
	int m = s + e >> 1;
	init(s, m, i << 1); init(m + 1, e, i << 1 | 1);
	t[i] = std::min(t[i << 1], t[i << 1 | 1]);
}

int get(int l, int r, int s = 1, int e = N, int i = 1) {
	if (r < s || e < l) return 1e9 + 7;
	if (l <= s && e <= r) return t[i];
	int m = s + e >> 1;
	return std::min(get(l, r, s, m, i << 1), get(l, r, m + 1, e, i << 1 | 1));
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	init();
	for (int i = 0, l, r; i < M; ++i) {
		std::cin >> l >> r;
		std::cout << get(l, r) << '\n';
	}
}