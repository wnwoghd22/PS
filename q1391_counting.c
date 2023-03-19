#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define LEN 2000

int N, A[LEN];
int sp, stack[LEN];
int seq[LEN];
int vps[LEN];
int temp[LEN]; // for sort

void counting_sort(int len) {
	int i, j;
	memset(temp, -1, sizeof temp);
	for (i = 0; i < len; ++i) temp[seq[i] - 1] = i;
	for (i = 0, j = 0; j < len; ++i)
		if (~temp[i])
			vps[j++] = temp[i];
}

void merge(int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) temp[k++] = seq[vps[i]] < seq[vps[j]] ? vps[i++] : vps[j++];
	while (i <= m) temp[k++] = vps[i++];
	while (j <= r) temp[k++] = vps[j++];
	for (k = l; k <= r; ++k) vps[k] = temp[k];
}
void merge_sort(int l, int r) {
	if (l == r) return;
	int m = l + r >> 1;
	merge_sort(l, m);
	merge_sort(m + 1, r);
	merge(l, m, r);
}
int check_vps(int* s, int len) {
	int i;
	sp = 0;
	for (i = 0; i < len; ++i) {
		if (s[i] & 1) {
			if (!sp || stack[--sp] - (s[i] >> 1))
				return 0;
		}
		else stack[sp++] = s[i] >> 1;
	}
	return 1;
}
int solve() {
	int d, i, l, r, k, t;
	scanf("%d", &N);
	for (i = 0; i < N; ++i) scanf("%d", A + i);
	for (d = 0; d < 2; ++d) {
		for (i = 0; i < N; ++i) vps[i] = i;
		for (i = d, k = 0; i < N - 1; i += 2, k += 2) {
			l = A[i], r = A[i + 1];
			if (l > r) t = l, l = r, r = t;
			seq[k] = l, seq[k + 1] = r;
		}
		// merge_sort(0, k - 1);
		counting_sort(k);
		if (!check_vps(vps, k)) return 0;
	}
	return 1;
}

int main() {
	freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--) printf("%s\n", solve() ? "YES" : "NO");
}