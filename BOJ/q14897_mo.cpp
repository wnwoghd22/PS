#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int LEN = 1000'000;

int N; 
int A[LEN], order[LEN], temp[LEN];
bool compA(int l, int r) { return A[l] < A[r]; }

int Q, sqrtN, count[LEN], cnt, result[LEN];
void push(int n) { if (!count[n]++) ++cnt; }
void pop(int n) { if (!--count[n]) --cnt; }
struct Query {
	int i, s, e;
	bool operator<(const Query& r) {
		if (s / sqrtN != r.s / sqrtN)
			return s / sqrtN < r.s / sqrtN;
		return e < r.e;
	}
} q[LEN];
bool compQ(int l, int r) { return q[l] < q[r]; }

void merge(int l, int r, int mid, bool (*compare)(int, int)) {
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) temp[k++] = compare(order[i], order[j]) ? order[i++] : order[j++];
	while (i <= mid) temp[k++] = order[i++];
	while (j <= r) temp[k++] = order[j++];
	for (i = l; i <= r; i++) order[i] = temp[i];
}
void merge_sort(int l, int r, bool (*compare)(int,int)) {
	if (l < r) {
		int mid = l + r >> 1;
		merge_sort(l, mid, compare);
		merge_sort(mid + 1, r, compare);
		merge(l, r, mid, compare);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	sqrtN = sqrt(N);
	for (int i = 0; i < N; ++i) std::cin >> A[i], order[i] = i;
	merge_sort(0, N - 1, compA);
	for (int i = 0, j = 0, k = A[order[0]]; i < N; ++i) {
		if (A[order[i]] ^ k) ++j, k = A[order[i]];
		A[order[i]] = j;
	}

	std::cin >> Q;
	for (int i = 0; i < Q; ++i) {
		std::cin >> q[i].s >> q[i].e;
		--q[i].s, --q[i].e;
		q[i].i = order[i] = i;
	}
	merge_sort(0, Q - 1, compQ);
	
	int s = q[order[0]].s, e = q[order[0]].e;
	for (int i = s; i <= e; ++i) push(A[i]);
	result[q[order[0]].i] = cnt;
	for (int i = 1; i < Q; ++i) {
		int idx = order[i];
		while (s > q[idx].s) push(A[--s]);
		while (e < q[idx].e) push(A[++e]);
		while (s < q[idx].s) pop(A[s++]);
		while (e > q[idx].e) pop(A[e--]);
		result[q[idx].i] = cnt;
	}
	for (int i = 0; i < Q; ++i) std::cout << result[i] << '\n';
}