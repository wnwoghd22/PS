#include <iostream>

const int LEN = 1e5 + 1;

int N, M, t[LEN << 2], ins[LEN];
void update(int x, int d, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) { t[i] = d; return; }
	int m = s + e >> 1;
	update(x, d, s, m, i << 1);
	update(x, d, m + 1, e, i << 1 | 1);
	t[i] = std::min(t[i << 1], t[i << 1 | 1]);
}
int nge(int k, int s = 1, int e = N, int i = 1) {
	if (t[i] >= k) return N + 1;
	if (s == e) return s;
	int m = s + e >> 1;
	int l = nge(k, s, m, i << 1);
	if (l <= N) return l;
	return nge(k, m + 1, e, i << 1 | 1);
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1, s; i <= N; ++i) {
		std::cin >> s;
		update(i, s - 1);
	}
	std::cin >> M;
	for (int i = 0, b; i < M; ++i) {
		std::cin >> b;
		int j = nge(b);
		if (j <= N) {
			ins[j] = 1;
			update(j, b);
		}
	}
	int ret = 0;
	for (int i = 1; i <= N; ++i) {
		if (ins[i]) ret++;
	}
	std::cout << ret;
}