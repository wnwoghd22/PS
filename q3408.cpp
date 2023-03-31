#include <iostream>

const int LEN = 200'000;
int T, N, A[LEN], order[LEN], next[LEN], before[LEN], temp[LEN];

void merge(int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) temp[k++] = A[order[i]] <= A[order[j]] ? order[i++] : order[j++];
	while (i <= m) temp[k++] = order[i++];
	while (j <= r) temp[k++] = order[j++];
	for (i = l; i <= r; ++i) order[i] = temp[i];
}

void merge_sort(int l, int r) {
	if (l == r) return;
	int m = l + r >> 1;
	merge_sort(l, m);
	merge_sort(m + 1, r);
	merge(l, m, r);
}

bool is_unique(int i, int l, int r) { return before[i] < l && r < next[i]; }

bool non_boring(int l, int r) {
	if (l >= r) return 1;
	for (int i = 0; i <= r - l >> 1; ++i) {
		if (is_unique(l + i, l, r)) return non_boring(l, l + i - 1) && non_boring(l + i + 1, r);
		if (is_unique(r - i, l, r)) return non_boring(l, r - i - 1) && non_boring(r - i + 1, r);
	}
	return 0;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		for (int i = 0; i < N; ++i) std::cin >> A[i], order[i] = i;
		merge_sort(0, N - 1);
		for (int i = 0; i < N - 1; ++i)
			next[order[i]] = A[order[i]] == A[order[i + 1]] ? order[i + 1] : N;
		next[order[N - 1]] = N;
		for (int i = N - 1; i > 0; --i)
			before[order[i]] = A[order[i]] == A[order[i - 1]] ? order[i - 1] : -1;
		before[order[0]] = -1;

		std::cout << (non_boring(0, N - 1) ? "non-boring\n" : "boring\n");
	}
}