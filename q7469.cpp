#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int LEN = 100'000;
const int INF = 2e9;

int N, M, A[LEN], v[LEN], len, c[LEN], o[LEN]; // value, compressed, order
int tree[17][LEN];

void merge(int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) tree[0][k++] = A[o[i]] <= A[o[j]] ? o[i++] : o[j++];
	while (i <= m) tree[0][k++] = o[i++];
	while (j <= r) tree[0][k++] = o[j++];
	for (i = l; i <= r; ++i) o[i] = tree[0][i];
}
void merge_sort(int l, int r) {
	if (l < r) {
		int m = l + r >> 1;
		merge_sort(l, m);
		merge_sort(m + 1, r);
		merge(l, m, r);
	}
}

void merge(int l, int m, int r, int d) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) tree[d][k++] = tree[d + 1][i] <= tree[d + 1][j] ? tree[d + 1][i++] : tree[d + 1][j++];
	while (i <= m) tree[d][k++] = tree[d + 1][i++];
	while (j <= r) tree[d][k++] = tree[d + 1][j++];
}
void merge_sort(int l, int r, int d) {
	if (l == r) tree[d][l] = c[l];
	else if (l < r) {
		int m = l + r >> 1;
		merge_sort(l, m, d + 1);
		merge_sort(m + 1, r, d + 1);
		merge(l, m, r, d);
	}
}

int upper_bound(int s, int e, int v, int d) {
	int l = s, r = e + 1, m;
	while (l < r) {
		m = l + r >> 1;
		if (tree[d][m] > v) r = m;
		else l = m + 1;
	}
	return r;
}

int query(int l, int r, int v, int s = 0, int e = N - 1, int d = 0) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) return upper_bound(s, e, v, d) - s;
	int m = s + e >> 1;
	return query(l, r, v, s, m, d + 1) + query(l, r, v, m + 1, e, d + 1);
}

int parametric_search(int l, int r, int k) {
	int lo = 0, hi = len - 1, m;
	while (lo < hi) {
		m = lo + hi >> 1;
		int cur = query(l, r, m);
		if (cur >= k) hi = m;
		else lo = m + 1;
	}
	return hi;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> A[i], o[i] = i;
	merge_sort(0, N - 1);
	for (int i = 0, j = -INF; i < N; ++i) {
		if (A[o[i]] ^ j)
			v[len++] = j = A[o[i]];
		c[o[i]] = len - 1;
	}
	// for (int i = 0; i < N; ++i) std::cout << c[i] << ' ';
	merge_sort(0, N - 1, 0);

	for (int m = 0, i, j, k; m < M; ++m) {
		std::cin >> i >> j >> k;
		std::cout << v[parametric_search(i - 1, j - 1, k)] << '\n';
	}
}