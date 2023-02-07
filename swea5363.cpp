#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>

typedef long long int ll;
const int LEN = 100'001;
const int MAX = 1'000'001;
const ll MOD = 1e9 + 7;

inline ll get_num() {
	ll num = 0, ch;
	while ((ch = getchar()) != EOF) {
		if (ch >= '0' && ch <= '9') num = num * 10 + ch - '0';
		else break;
	}
	return num;
}

ll t = 1, T, N, Q, sqrtN, A[LEN], count[MAX], sum, total;
void push(int n) { sum -= count[n] * count[n] * n; ++count[n]; sum += count[n] * count[n] * n; }
void pop(int n) { sum -= count[n] * count[n] * n; --count[n]; sum += count[n] * count[n] * n; }
struct Query {
	int index, s, e;
	bool operator<(const Query& r) { return s / sqrtN ^ r.s / sqrtN ? s / sqrtN < r.s / sqrtN : e < r.e; }
} q[LEN];
int index[LEN], temp[LEN];

void merge(int l, int r, int mid) {
	int i = l, j = mid + 1, k = 0;
	while (i <= mid && j <= r) temp[k++] = q[i] < q[j] ? index[i++] : index[j++];
	while (i <= mid) temp[k++] = index[i++];
	while (j <= r) temp[k++] = index[j++];
	for (i = l; i <= r; i++) index[i] = temp[i - l];
}

void merge_sort(int l, int r) {
	int mid;
	if (l < r) {
		mid = (l + r) / 2;
		merge_sort(l, mid);
		merge_sort(mid + 1, r);
		merge(l, r, mid);
	}
}

ll solve() {
	sum = 0, total = 0;
	memset(count, 0, sizeof count);
	N = get_num(); Q = get_num();
	sqrtN = sqrt(N);
	for (int i = 1; i <= N; ++i) A[i] = get_num();
	for (int i = 0; i < Q; ++i) {
		index[i] = i;
		q[i].index = i + 1;
		q[i].s = get_num(); q[i].e = get_num();
	}
	merge_sort(0, Q - 1);
	int s = q[index[0]].s, e = q[index[0]].e;
	for (int i = s; i <= e; ++i) push(A[i]);
	total += sum * q[index[0]].index % MOD;
	total %= MOD;

	for (int i = 1; i < Q; ++i) {
		int idx = index[i];
		while (s < q[idx].s) pop(A[s++]);
		while (s > q[idx].s) push(A[--s]);
		while (e < q[idx].e) push(A[++e]);
		while (e > q[idx].e) pop(A[e--]);
		total += sum * q[idx].index % MOD;
		total %= MOD;
	}
	return total;
}
int main() {
	T = get_num();
	for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}