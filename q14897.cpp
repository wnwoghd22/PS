#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int LEN = 1000'000;

int N; 
int A[LEN], order[LEN], temp[LEN];
void merge_order(int l, int r, int mid) {
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) temp[k++] = A[order[i]] < A[order[j]] ? order[i++] : order[j++];
	while (i <= mid) temp[k++] = order[i++];
	while (j <= r) temp[k++] = order[j++];
	for (i = l; i <= r; i++) order[i] = temp[i];
}
void merge_sort_order(int l, int r) {
	int mid;
	if (l < r) {
		mid = (l + r) / 2;
		merge_sort_order(l, mid);
		merge_sort_order(mid + 1, r);
		merge_order(l, r, mid);
	}
}

int Q, sqrtN, count[LEN], cnt, result[LEN];
void push(int n) { if (!count[n]++) ++cnt; }
void pop(int n) { if (!--count[n]) --cnt; }
struct Query {
	int index, s, e;
	bool operator<(const Query& r) {
		if (s / sqrtN != r.s / sqrtN)
			return s / sqrtN < r.s / sqrtN;
		return e < r.e;
	}
} q[LEN];

void merge_query(int l, int r, int mid) {
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) temp[k++] = q[order[i]] < q[order[j]] ? order[i++] : order[j++];
	while (i <= mid) temp[k++] = order[i++];
	while (j <= r) temp[k++] = order[j++];
	for (i = l; i <= r; i++) order[i] = temp[i];
}
void merge_sort_query(int l, int r) {
	int mid;
	if (l < r) {
		mid = (l + r) / 2;
		merge_sort_query(l, mid);
		merge_sort_query(mid + 1, r);
		merge_query(l, r, mid);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	sqrtN = sqrt(N);
	for (int i = 0; i < N; ++i) std::cin >> A[i], order[i] = i;
	merge_sort_order(0, N - 1);
	for (int i = 0, j = 0, k = A[order[0]]; i < N; ++i) {
		if (A[order[i]] ^ k) ++j, k = A[order[i]];
		A[order[i]] = j;
	}
	// for (int i = 0; i < N; ++i) std::cout << A[i] << ' ';
	std::cin >> Q;
	for (int i = 0; i < Q; ++i) std::cin >> q[i].s >> q[i].e, q[i].s--, q[i].e--, q[i].index = order[i] = i;
	merge_sort_query(0, Q - 1);
	
	int s = q[order[0]].s, e = q[order[0]].e;
	for (int i = s; i <= e; ++i) push(A[i]);
	result[q[order[0]].index] = cnt;

	for (int i = 1; i < Q; ++i) {
		int idx = order[i];
		while (s < q[idx].s) pop(A[s++]);
		while (s > q[idx].s) push(A[--s]);
		while (e < q[idx].e) push(A[++e]);
		while (e > q[idx].e) pop(A[e--]);
		// std::cout << q[idx].index << ' ' << cnt << '\n';
		result[q[idx].index] = cnt;
	}

	for (int i = 0; i < Q; ++i) std::cout << result[i] << '\n';
}