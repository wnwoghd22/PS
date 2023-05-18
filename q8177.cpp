#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 200'001;
const ll INF = 2e17;

ll N, M, K, D, A[LEN], R, X, Q;

struct Node {
	ll lm, rm, sum, max;
	Node operator+(const Node& r) const {
		return {
			std::max(lm, sum + r.lm),
			std::max(r.rm, rm + r.sum),
			sum + r.sum,
			std::max({ max, r.max, rm + r.lm })
		};
	}
} seg_tree[LEN << 2];

void update(int x, ll d, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) {
		seg_tree[i].lm = seg_tree[i].rm = seg_tree[i].sum = seg_tree[i].max = A[i] += d;
		return;
	}
	int m = s + e >> 1;
	update(x, d, s, m, i << 1); update(x, d, m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] + seg_tree[i << 1 | 1];
}
ll get_max() { return seg_tree[1].max; }

int main() {
	std::cin >> N >> M >> K >> D;
	for (int i = 1; i <= N; ++i) update(i, -K);
	Q = K * D;

	while (M--) {
		std::cin >> R >> X;
		update(R, X);
		std::cout << (get_max() <= Q ? "TAK\n" : "NIE\n");
	}
}