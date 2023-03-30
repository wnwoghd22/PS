#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int INF = 1e9;
const int LEN = 1e6;
int N, Q, A[LEN], O[LEN], tree[21][LEN];

void merge(int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) tree[0][k++] = A[O[i]] <= A[O[j]] ? O[i++] : O[j++];
	while (i <= m) tree[0][k++] = O[i++];
	while (j <= r) tree[0][k++] = O[j++];
	for (i = l; i <= r; ++i) O[i] = tree[0][i];
}
void merge_sort(int l, int r) {
	if (l < r) {
		int m = l + r >> 1;
		merge_sort(l, m);
		merge_sort(m + 1, r);
		merge(l, m, r);
	}
}

void merge(int d, int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) tree[d][k++] = tree[d + 1][i] <= tree[d + 1][j] ? tree[d + 1][i++] : tree[d + 1][j++];
	while (i <= m) tree[d][k++] = tree[d + 1][i++];
	while (j <= r) tree[d][k++] = tree[d + 1][j++];
}
void merge_sort(int d, int l, int r) {
	if (l == r) tree[d][l] = A[l];
	else {
		int m = l + r >> 1;
		merge_sort(d + 1, l, m);
		merge_sort(d + 1, m + 1, r);
		merge(d, l, m, r);
	}
}
int upper_bound(int k, int s, int e, int d) {
	int l = s, r = e + 1, m;
	while (l < r) {
		m = l + r >> 1;
		if (tree[d][m] > k) r = m;
		else l = m + 1;
	}
	return r;
}
int query(int l, int r, int k, int s = 0, int e = N - 1, int d = 0) {
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) return e - upper_bound(k, s, e, d) + 1;
	int m = s + e >> 1;
	return query(l, r, k, s, m, d + 1) + query(l, r, k, m + 1, e, d + 1);
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 0; i < N; ++i)
		std::cin >> A[i], O[i] = i;
	merge_sort(0, N - 1);
	for (int i = 0; i < N - 1; ++i)
		A[O[i]] = A[O[i]] == A[O[i + 1]] ? O[i + 1] : INF;
	A[N - 1] = INF;
	for (int i = 0; i < N; ++i)
		std::cout << A[i] << ' ';
	std::cout << '\n';

	merge_sort(0, 0, N - 1);
	std::cin >> Q;
	for (int q = 0, l, r; q < Q; ++q) {
		std::cin >> l >> r;
		std::cout << query(l - 1, r - 1, r - 1) << '\n';
	}
}