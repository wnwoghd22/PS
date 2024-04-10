#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef long long ll;
const ll INF = 1e18;
const int LEN = 262'143;
struct Node { // for seg tree
	ll l, r, sum, max;
	void init() { l = r = sum = 0; max = -INF; }
	void operator+=(const ll& w) {
		if (max == -INF) l = r = sum = max = 0;
		l = r = sum = max += w;
	}
	ll L() const { return max == -INF ? -INF : l; }
	ll R() const { return max == -INF ? -INF : r; }
	Node operator+(const Node& rhs) const {
		return {
			std::max(L(), sum + rhs.L()),
			std::max(R() + rhs.sum, rhs.R()),
			sum + rhs.sum,
			std::max({ max, rhs.max, R() + rhs.L() })
		};
	}
} seg_tree[LEN * 4];
ll N, W[LEN + 1];

void update(int y, ll w, int s = 1, int e = N, int i = 1) {
	if (e < y || y < s) return;
	if (s == e) return seg_tree[i] += w;
	int m = s + e >> 1;
	update(y, w, s, m, i << 1), update(y, w, m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] + seg_tree[i << 1 | 1];
}
ll get_max() { return seg_tree[1].max; }

struct Info {
	ll w;
	int x, y;
	bool operator<(const Info& r) const { return x > r.x; }
};

int y;
std::vector<Info> query;
void dfs(int i, int x) {
	if (i * 2 <= N) dfs(i * 2, x + 1);
	query.push_back({ W[i], x, ++y });
	if (i * 2 + 1 <= N) dfs(i * 2 + 1, x + 1);
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> W[i];
	dfs(1, 0);
	std::sort(query.begin(), query.end());
	// for (const Info& i : query) std::cout << i.x << ' ' << i.y << ' ' << i.w << '\n';
	ll max = -INF;
	// std::cout << log2(N) << '\n';
	for (int x = log2(N), p = 0; x >= 0; --x) {
		for (int i = 0; i <= N * 4; ++i) seg_tree[i].init();

		// std::cout << x << ' ' << p << '\n';
		while (p < N && query[p].x == x) update(query[p].y, query[p].w), ++p;
		if (get_max() > max) max = get_max();
		for (int dx = x - 1, i = p; dx >= 0; --dx) {
			while (i < N && query[i].x == dx) update(query[i].y, query[i].w), ++i;

			if (get_max() > max) max = get_max();
		}
	}
	std::cout << max;
}