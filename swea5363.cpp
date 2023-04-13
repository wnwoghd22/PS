#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cstring>

typedef long long int ll;
const int LEN = 100'001;
const int MAX = 1'000'001;
const ll MOD = 1e9 + 7;

int t = 1, T, N, Q, sqrtN;
ll sum, total, A[LEN], count[MAX];
struct Query {
	int index, s, e;
	bool operator<(const Query& r) const {
		int le = e / sqrtN;
		int re = r.e / sqrtN;
		if (le == re) return s < r.s;
		return le < re;
	}
} q[LEN];
int _index[LEN], temp[LEN];

void merge(int l, int r, int mid) {
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) temp[k++] = q[_index[i]] < q[_index[j]] ? _index[i++] : _index[j++];
	while (i <= mid) temp[k++] = _index[i++];
	while (j <= r) temp[k++] = _index[j++];
	for (i = l; i <= r; ++i) _index[i] = temp[i];
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

int solve() {
	sum = 0, total = 0;
	memset(count, 0, sizeof count);
	scanf("%d %d", &N, &Q);
	sqrtN = sqrt(N);
	for (int i = 1; i <= N; ++i) scanf("%lld", A + i);
	for (int i = 0; i < Q; ++i) {
		_index[i] = i;
		q[i].index = i + 1;
		scanf("%d %d", &q[i].s, &q[i].e);
	}
	merge_sort(0, Q - 1);

	sum = A[1];
	++count[A[1]];
	for (int i = 0, s = 1, e = 1; i < Q; ++i) {
		int idx = _index[i];
		int qs = q[idx].s, qe = q[idx].e;
		for (int j = s; j < qs; ++j) {
			--count[A[j]];
			sum -= A[j] * (count[A[j]] * 2 + 1);
		}
		for (int j = s - 1; j >= qs; --j) {
			sum += A[j] * (count[A[j]] * 2 + 1);
			++count[A[j]];
		}
		for (int j = e + 1; j <= qe; ++j) {
			sum += A[j] * (count[A[j]] * 2 + 1);
			++count[A[j]];
		}
		for (int j = e; j > qe; --j) {
			--count[A[j]];
			sum -= A[j] * (count[A[j]] * 2 + 1);
		}
		s = qs;
		e = qe;
		// sum %= MOD;
		total += sum % MOD * q[idx].index % MOD;
		total %= MOD;
	}
	return total;
}
int main() {
	scanf("%d", &T);
	for (t = 1; t <= T; ++t)
		printf("#%d %d\n", t, solve());
}