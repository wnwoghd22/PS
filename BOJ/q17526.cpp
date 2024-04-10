#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

typedef long long int ll;
const ll INF = 1e17;
const int LEN = 100'001;

struct Line {
	ll a, b;
	Line() {}
	Line(ll a, ll b) : a(a), b(b) {}
	ll f(ll x) { return a * x + b; }
};

class LiChaoTree {
	struct Node {
		int r, l; // children
		ll s, e;
		Line line;
	};
	std::vector<Node> tree;
	void update(int node, Line l) {
		ll s = tree[node].s, e = tree[node].e;
		ll m = (s + e) >> 1;

		Line low = tree[node].line, high = l;
		if (high.f(s) < low.f(s)) std::swap(low, high);

		if (low.f(e) <= high.f(e)) {
			tree[node].line = low;
			return;
		}
		if (low.f(m) <= high.f(m)) { // left side is low-dominant, cross at right
			tree[node].line = low;
			if (!~tree[node].r) {
				tree[node].r = tree.size();
				tree.push_back({ -1, -1, m + 1, e, {0, INF} });
			}
			update(tree[node].r, high);
		}
		else { // right side is high-dominant, cross at left
			tree[node].line = high;
			if (!~tree[node].l) {
				tree[node].l = tree.size();
				tree.push_back({ -1, -1, s, m, {0, INF} });
			}
			update(tree[node].l, low);
		}
	}
	ll get(int node, ll x) {
		if (!~node) return INF;
		Node& n = tree[node];
		ll s = n.s, e = n.e;
		ll m = (s + e) >> 1;
		if (x <= m) return std::min(n.line.f(x), get(n.l, x));
		else return std::min(n.line.f(x), get(n.r, x));
	}
public:
	LiChaoTree(ll s, ll e) { tree.push_back({ -1, -1, s, e, {0, INF} }); }
	void add_line(ll a, ll b) { update(0, { a, b }); }
	ll query(ll x) { return get(0, x); }
};

ll N, dist[LEN], S[LEN], P[LEN], dp[LEN];

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 2; i <= N; ++i) {
		std::cin >> dist[i];
		dist[i] += dist[i - 1];
	}
	for (int i = 1; i < N; ++i)
		std::cin >> P[i] >> S[i];

	LiChaoTree hull(0, dist[N]);
	hull.add_line(S[1], P[1]);
	for (int i = 2; i <= N; ++i) {
		dp[i] = hull.query(dist[i]);
		hull.add_line(S[i], dp[i] + P[i] - S[i] * dist[i]);
	}
	std::cout << dp[N];
}