#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

const int LEN = 1200;
int A[LEN], temp[LEN];

void merge(int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) temp[k++] = A[i] <= A[j] ? A[i++] : A[j++];
	while (i <= m) temp[k++] = A[i++];
	while (j <= r) temp[k++] = A[j++];
	for (i = l; i <= r; i++) A[i] = temp[i];
}
void merge_sort(int l, int r) {
	if (l < r) {
		int m = l + r >> 1;
		merge_sort(l, m);
		merge_sort(m + 1, r);
		merge(l, m, r);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	int h, c, H, M, S;
	scanf("%d%d", &h, &c);
	for (int i = 0; i < h + c; ++i) {
		scanf(" %d:%d:%d ", &H, &M, &S);
		A[i] = H * 3600 + M * 60 + S;
	}
	merge_sort(0, h + c - 1);
	int total = 24 * 60 * 60;
	int line = 0, l = 0, r = 0;

	// sweeping
	for (int i = 0; i < h + c; ++i) {
		if (A[i] > r) line += r - l, l = A[i], r = A[i] + 40;
		else r += 40 - r + A[i];
		printf("A: %d, l: %dm r: %d\n", A[i], l, r);
	}
	line += r - l;
	printf("%d", total - line);
}