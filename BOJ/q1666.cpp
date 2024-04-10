#include <iostream>
#include <algorithm>

const int LEN = 1e5;
const int MAX = 1 << 17;

struct Pos {
	int x, y, d, i;
	bool operator<(const Pos& r) const {
		if (x != r.x) return x < r.x;
		if (d != r.d) return d < r.d;
		return y < r.y;
	}
} p[LEN << 1];

int N, dp[LEN], t[MAX << 1];
void update(int x, int v) {
	x += MAX - 1;
	t[x] = std::max(t[x], v);
	for (x >>= 1; x >= 1; x >>= 1)
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
}

int query(int l, int r) {
	l += MAX - 1;
	r += MAX - 1;
	int ret = 0;
	for (; l <= r; l >>= 1, r >>= 1) {
		if (l & 1) ret = std::max(ret, t[l++]);
		if (~r & 1) ret = std::max(ret, t[r--]);
	}
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> p[i << 1].x >> p[i << 1].y;
		std::cin >> p[i << 1 | 1].x >> p[i << 1 | 1].y;
		p[i << 1].i = p[i << 1 | 1].i = i;
		p[i << 1].d = 0; p[i << 1 | 1].d = 1;
	}
	std::sort(p, p + N * 2);
	for (int i = 0; i < N * 2; ++i) {
		if (p[i].d) update(p[i].y, dp[p[i].i]);
		else dp[p[i].i] = query(0, p[i].y - 1) + 1;
	}
	std::cout << query(0, LEN);
}