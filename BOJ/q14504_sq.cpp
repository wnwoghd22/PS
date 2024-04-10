#include <iostream>
#include <cmath>

const int LEN = 100'200;
int N, sqN, M, A[LEN], tree[10][LEN];

void merge(int l, int m, int r, int d) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) tree[d][k++] = tree[d + 1][i] <= tree[d + 1][j] ? tree[d + 1][i++] : tree[d + 1][j++];
	while (i <= m) tree[d][k++] = tree[d + 1][i++];
	while (j <= r) tree[d][k++] = tree[d + 1][j++];
}

void merge_sort(int l, int r, int d = 0) {
	if (l == r) tree[d][l] = A[l];
	else {
		int m = l + r >> 1;
		merge_sort(l, m, d + 1);
		merge_sort(m + 1, r, d + 1);
		merge(l, m, r, d);
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

int query(int l, int r, int k, int s, int e, int d = 0) {
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) return e - upper_bound(k, s, e, d) + 1;
	int m = s + e >> 1;
	return query(l, r, k, s, m, d + 1) + query(l, r, k, m + 1, e, d + 1);
}

int query(int i, int j, int k) {
	int s = i / sqN, e = j / sqN, result = 0;
	for (int l = s; l <= e; ++l)
		result += query(i, j, k, l * sqN, (l + 1) * sqN - 1);
	return result;
}

void update(int i, int k) {
	A[i] = k;
	int s = (i / sqN) * sqN;
	merge_sort(s, s + sqN - 1);
}

int main() {
	std::cin >> N;
	sqN = sqrt(N);
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	for (int i = 0; i < N; i += sqN) merge_sort(i, i + sqN - 1); // init
	
	std::cin >> M;
	for (int m = 0, q, i, j, k; m < M; ++m) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> i >> j >> k;
			std::cout << query(--i, --j, k) << '\n';
		}
		if (q == 2) {
			std::cin >> i >> k;
			update(--i, k);
		}
	}
}