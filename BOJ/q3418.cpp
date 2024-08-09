#include <iostream>
#include <algorithm>

/* algorithm
 * 
 * - make linked-list that links elements a_i and a_j if a_i == a_j
 * - make min seg tree of left pointers and max seg tree of right pointers of linked list.
 * - check each query that
 * - right_poninters.min(s, e) > e and
 * - left_pointers.max(s, e) < s
 * - if both are true, then every elements between s and e are unique.
 * - if not, then find arbitrary and print.
 */

const int LEN = 1'000'001;

int M, Q, K[LEN];
int left[LEN], right[LEN]; // pointers

struct E {
	int i, a;
	bool operator<(const E& o) const {
		return a == o.a ? i < o.i : a < o.a;
	}
} e[LEN];

int max_t[LEN << 2], min_t[LEN << 2];
int init_max(int s = 1, int e = M, int i = 1) {
	if (s == e) { max_t[i] = s; return s; }
	int m = s + e >> 1;
	int l = init_max(s, m, i << 1), r = init_max(m + 1, e, i << 1 | 1);
	return max_t[i] = left[l] > left[r] ? l : r;
}
int get_max(int l, int r, int s = 1, int e = M, int i = 1) {
	if (r < s || e < l) return M + 1;
	if (l <= s && e <= r) return max_t[i];
	int m = s + e >> 1;
	int _l = get_max(l, r, s, m, i << 1);
	int _r = get_max(l, r, m + 1, e, i << 1 | 1);
	return left[_l] > left[_r] ? _l : _r;
}

int init_min(int s = 1, int e = M, int i = 1) {
	if (s == e) { min_t[i] = s; return s; }
	int m = s + e >> 1;
	int l = init_min(s, m, i << 1), r = init_min(m + 1, e, i << 1 | 1);
	return min_t[i] = right[l] < right[r] ? l : r;
}
int get_min(int l, int r, int s = 1, int e = M, int i = 1) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) return min_t[i];
	int m = s + e >> 1;
	int _l = get_min(l, r, s, m, i << 1);
	int _r = get_min(l, r, m + 1, e, i << 1 | 1);
	return right[_l] < right[_r] ? _l : _r;
}

void solve() {
	for (int i = 0; i < M; ++i) {
		std::cin >> K[i];
		e[i] = { i + 1, K[i] };
	}
	std::sort(e, e + M);

	// make linked list
	left[e[0].i] = -1;
	for (int i = 1; i < M; ++i) {
		if (e[i].a != e[i - 1].a) left[e[i].i] = -1;
		else left[e[i].i] = e[i - 1].i;
	} left[M + 1] = -1;

	right[e[M - 1].i] = M + 1;
	for (int i = M - 2; i >= 0; --i) {
		if (e[i].a != e[i + 1].a) right[e[i].i] = M + 1;
		else right[e[i].i] = e[i + 1].i;
	} right[0] = M + 1;

	init_min();
	init_max();

	for (int q = 0, b, e; q < Q; ++q) {
		std::cin >> b >> e;
		int min = get_min(b, e);
		int max = get_max(b, e);

		if (right[min] > e && left[max] < b) std::cout << "OK\n";
		else std::cout << K[min - 1] << '\n';
	}
	std::cout << '\n';
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	while (1) {
		std::cin >> M >> Q;
		if (!M && !Q) break;
		solve();
	}
}