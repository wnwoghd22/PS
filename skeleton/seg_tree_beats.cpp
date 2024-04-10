#include <iostream>

const int LEN = 1'000'001;
typedef long long ll;

struct Node {
	ll mx, mx2, mx_cnt, sum;
	Node operator+(const Node& r) const {
		if (mx == r.mx) return { mx, std::max(mx2, r.mx2), mx_cnt + r.mx_cnt, sum + r.sum };
		if (mx > r.mx) return { mx, std::max(mx2, r.mx), mx_cnt, sum + r.sum };
		if (mx < r.mx) return { r.mx, std::max(mx, r.mx2), r.mx_cnt, sum + r.sum };
	}
} seg_tree[LEN];

int N, M;

void propagate(int s, int e, int i) {
	if (s ^ e) {
		for (int j = 0; j < 2; ++j) {
			Node& child = seg_tree[i << 1 | j];
			if (child.mx > seg_tree[i].mx) {
				child.sum -= child.mx_cnt * (child.mx - seg_tree[i].mx);
				child.mx = seg_tree[i].mx;
			}
		}
	}
}

void update(int l, int r, ll x, int s = 1, int e = N, int i = 1) {
	propagate(s, e, i);
	if (e < l || r < s || seg_tree[i].mx <= x) return;
	if (l <= s && e <= r && seg_tree[i].mx2 < x) {
		seg_tree[i].sum -= seg_tree[i].mx_cnt * (seg_tree[i].mx - x);
		seg_tree[i].mx = x;
		// propagate(s, e, i);
		return;
	}
	int m = s + e >> 1;
	update(l, r, x, s, m, i << 1);
	update(l, r, x, m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] + seg_tree[i << 1 | 1];
}

ll get_max(int l, int r, int s = 1, int e = N, int i = 1) {
	propagate(s, e, i);
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) return seg_tree[i].mx;
	int m = s + e >> 1;
	return std::max(get_max(l, r, s, m, i << 1), get_max(l, r, m + 1, e, i << 1 | 1));
}

ll get_sum(int l, int r, int s = 1, int e = N, int i = 1) {
	propagate(s, e, i);
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) return seg_tree[i].sum;
	int m = s + e >> 1;
	return get_sum(l, r, s, m, i << 1) + get_sum(l, r, m + 1, e, i << 1 | 1);
}

ll A[LEN];

void init(int s = 1, int e = N, int i = 1) {
	if (s == e) { seg_tree[i] = { A[s], -1, 1, A[s] }; return; }
	int m = s + e >> 1;
	init(s, m, i << 1); init(m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] + seg_tree[i << 1 | 1];
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);

	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	init();

	std::cin >> M;
	for (int i = 0, q, l, r, x; i < M; ++i) {
		std::cin >> q >> l >> r;
		if (q == 1) std::cin >> x, update(l, r, x);
		if (q == 2) std::cout << get_max(l, r) << '\n';
		if (q == 3) std::cout << get_sum(l, r) << '\n';
	}
}