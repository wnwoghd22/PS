#include <iostream>
#include <algorithm>
#include <vector>

const int LEN = 500'001;
const int INF = 2e9 + 1;

int N, U, D, S;

struct SegTree {
	int t[LEN << 2];
	void init() { for (int i = 0; i < (LEN << 2); ++i) t[i] = -INF; }
	void update(int x, int d, int s = 0, int e = LEN, int i = 1) {
		if (x < s || e < x) return;
		if (s == e) { t[i] = d; return; }
		int m = s + e >> 1;
		update(x, d, s, m, i << 1); update(x, d, m + 1, e, i << 1 | 1);
		t[i] = std::max(t[i << 1], t[i << 1 | 1]);
	}
	int get_max(int l, int r, int s = 0, int e = LEN, int i = 1) {
		if (r < s || e < l) return -INF;
		if (l <= s && e <= r) return t[i];
		int m = s + e >> 1;
		return std::max(get_max(l, r, s, m, i << 1), get_max(l, r, m + 1, e, i << 1 | 1));
	}
} seg_u, seg_d;
void init() { seg_u.init(); seg_d.init(); }
void update(int x, int d) { seg_u.update(x, d - U * x); seg_d.update(x, d + D * x); }
int get_max(int x) { return std::max(seg_u.get_max(x, LEN - 1) + U * x, seg_d.get_max(0, x) - D * x); }

struct Market {
	int l, m;
	bool operator<(const Market& r) const { return l < r.l; }
};
std::vector<Market> markets[LEN];

int dp[2][LEN];

int main() {
	std::cin >> N >> U >> D >> S;
	for (int i = 0, T, L, M; i < N; ++i) {
		std::cin >> T >> L >> M;
		markets[T].push_back({ L, M });
	}
	init();

	update(S, 0);

	for (std::vector<Market>& ms : markets) {
		if (ms.empty()) continue;
		std::sort(ms.begin(), ms.end());
		int len = ms.size();
		for (int i = 0; i < len; ++i)
			dp[0][i] = dp[1][i] = get_max(ms[i].l);

		dp[0][0] += ms[0].m;
		for (int i = 1; i < len; ++i) {
			dp[0][i] = std::max(dp[0][i], dp[0][i - 1] - D * (ms[i].l - ms[i - 1].l));
			dp[0][i] += ms[i].m;
		}
		dp[1][len - 1] += ms[len - 1].m;
		for (int i = len - 2; i >= 0; --i) {
			dp[1][i] = std::max(dp[1][i], dp[1][i + 1] - U * (ms[i + 1].l - ms[i].l));
			dp[1][i] += ms[i].m;
		}
		for (int i = 0; i < len; ++i) update(ms[i].l, std::max(dp[0][i], dp[1][i]));
	}

	std::cout << get_max(S);
}