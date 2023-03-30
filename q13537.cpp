#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int LEN = 100'000;
int N, M, A[LEN], tree[20][LEN];

void merge(int d, int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) tree[d][k++] = tree[d + 1][i] < tree[d + 1][j] ? tree[d + 1][i++] : tree[d + 1][j++];
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
	std::cout << "upper bound: " << s << ' ' << e << ' ' << d << '\n';
	std::cout << "target: " << k << '\n';
	std::cout << "arr: ";
	for (int i = s; i <= e; ++i) std::cout << tree[d][i] << ' ';
	std::cout << '\n';
	int l = s, r = e + 1, m;
	while (l < r) {
		m = l + r >> 1;
		if (tree[d][m] > k) r = m;
		else l = m + 1;
	}

	std::cout << ", result: " << r << '\n';
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
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	merge_sort(0, 0, N - 1);
	for (int d = 0; d < 4; ++d) {
		for (int i = 0; i < N; ++i)
			std::cout << tree[d][i] << ' ';
		std::cout << '\n';
	}
	std::cin >> M;
	for (int m = 0, i, j, k; m < M; ++m) {
		std::cin >> i >> j >> k;
		std::cout << query(i - 1, j - 1, k) << '\n';
	}
}