#include <iostream>
#include <algorithm>
#include <map>

const int LEN = 1 << 17;

int N, M, K, A[LEN], O[LEN], pre[LEN];
struct E {
	int A, i;
	bool operator<(const E& r) const { return A == r.A ? i < r.i : A < r.A; }
} arr[LEN];

int sz = 2;
struct Node { // for PST
	int val, l, r;
} pst[LEN << 9];

int _update(int s, int e, int x, int d, int prev) {
	Node p = pst[prev];
	if (s == e) {
		pst[sz].val = p.val + d;
		return sz++;
	}
	int m = s + e >> 1;
	int l = x <= m ? _update(s, m, x, d, p.l) : p.l;
	int r = x <= m ? p.r : _update(m + 1, e, x, d, p.r);
	pst[sz] = { pst[l].val + pst[r].val, l, r };
	return sz++;
}
int _update(int x, int d, int prev) { return _update(0, N, x, d, prev); } // return root index

int _get_cnt(int x, int i, int s = 0, int e = N) { // get count sum from point x to right end
	// std::cout << "node" << i << ", from " << x << '\n';
	if (!i) return 0;
	Node n = pst[i];
	if (x <= s) return n.val;
	if (e < x) return 0;
	int m = s + e >> 1;
	return _get_cnt(x, n.l, s, m) + _get_cnt(x, n.r, m + 1, e);
}

std::map<int, int> PST[LEN << 2];
int _prev[LEN << 2];

void update(int a, int x, int s, int e, int i) {
	if (a < s || e < a) return;
	int root = _prev[i];
	int r1 = _update(pre[x], -1, root);
	int r2 = _update(x + 1, 1, r1);
	PST[i][x + 1] = _prev[i] = r2;
	if (s == e) return;
	int m = s + e >> 1;
	update(a, x, s, m, i << 1);
	update(a, x, m + 1, e, i << 1 | 1);
}
void update(int a, int x) { update(a, x, 1, K, 1); }

int find(int l, int r, int k, int s, int e, int i) {
	if (s == e) return s;
	int m = s + e >> 1;
	auto it = PST[i << 1].upper_bound(r);
	int cnt = it != PST[i << 1].begin() ? _get_cnt(l, (--it)->second) : 0;
	// std::cout << s << '~' << e << ',' << l << '~' << r << ':' << cnt << '\n';
	if (cnt >= k) return find(l, r, k, s, m, i << 1);
	return find(l, r, k - cnt, m + 1, e, i << 1 | 1);
}
int find(int l, int r, int k) { return find(l, r, k, 1, K, 1); }

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0, a; i < N; ++i) {
		std::cin >> a;
		arr[i] = { a, i };
	}
	std::sort(arr, arr + N);
	for (int i = 0, j = 0; i < N; ++i) {
		if (j != arr[i].A) {
			pre[arr[i].i] = 0;
			j = A[K++] = arr[i].A;
		}
		else pre[arr[i].i] = arr[i - 1].i + 1;
		O[arr[i].i] = K;
	}
	++K;
	for (int i = 1; i < LEN << 1; ++i) PST[i][0] = 1;
	for (int i = 0; i < N; ++i) {
		// std::cout << "update: " << i << ' ' << O[i] << ' ' << pre[i] << '\n';
		update(O[i], i);
	}

	std::cin >> M;
	for (int i = 0, a, b, c, d, k, l, r, ans = 0; i < M; ++i) {
		std::cin >> a >> b >> c >> d >> k;
		l = ((long long)a * std::max(ans, 0) + b) % N + 1;
		r = ((long long)c * std::max(ans, 0) + d) % N + 1;
		if (l > r) std::swap(l, r);
		ans = find(l, r, k);
		// std::cout << ans << ' ';
		if (ans == K) ans = -1;
		else ans = A[ans - 1];
		std::cout << ans << '\n';
	}
}