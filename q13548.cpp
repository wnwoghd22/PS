#include <iostream>
#include <cmath>
#include <algorithm>

const int LEN = 100'001;

int N, M, sqrtN, A[LEN], answer[LEN], count[LEN], seg_tree[LEN * 4];

int get_max() { return seg_tree[1]; }
int update_max(int n, int start = 1, int end = LEN - 1, int index = 1) {
	if (n > end || n < start) return seg_tree[index];
	if (start == end) return seg_tree[index] = count[n];
	int mid = (start + end) / 2;
	return seg_tree[index] = std::max(update_max(n, start, mid, index * 2), update_max(n, mid + 1, end, index * 2 + 1));
}

struct Query {
	int index, s, e;
	bool operator<(const Query& r) { return s / sqrtN ^ r.s / sqrtN ? s / sqrtN < r.s / sqrtN : e < r.e; }
} q[LEN];

int main() {
	std::cin >> N;
	sqrtN = sqrt(N);
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	std::cin >> M;
	for (int i = 0; i < M; ++i) {
		q[i].index = i;
		std::cin >> q[i].s >> q[i].e;
	}
	std::sort(q, q + M);
	int s = q[0].s, e = q[0].e;
	for (int i = s; i <= e; ++i) {
		count[A[i]]++;
		update_max(A[i]);
	}
	answer[q[0].index] = get_max();
	for (int i = 1; i < M; ++i) {
		while (s < q[i].s) --count[A[s]], update_max(A[s++]);
		while (s > q[i].s) ++count[A[--s]], update_max(A[s]);
		while (e < q[i].e) ++count[A[++e]], update_max(A[e]);
		while (e > q[i].e) --count[A[e]], update_max(A[e--]);
		answer[q[i].index] = get_max();
	}
	for (int i = 0; i < M; ++i) std::cout << answer[i] << '\n';
}