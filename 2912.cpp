#include <iostream>
#include <cmath>
#include <algorithm>

const int LEN = 300'001;

int N, C, M, sqrtN, A[LEN], answer[LEN], count[LEN], num[LEN] = { LEN, }, max = 0;

void add_count(int n) {
	if (count[n] == max) ++max;
	--num[count[n]++], ++num[count[n]];
}

void pop_count(int n) {
	if (count[n] == max && num[count[n]] == 1) --max;
	--num[count[n]--], ++num[count[n]];
}

struct Query {
	int index, s, e;
	bool operator<(const Query& r) { return s / sqrtN ^ r.s / sqrtN ? s / sqrtN < r.s / sqrtN : e < r.e; }
} q[LEN];

int main() {
	std::cin >> N >> C;
	sqrtN = sqrt(N);
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	std::cin >> M;
	for (int i = 0; i < M; ++i) {
		q[i].index = i;
		std::cin >> q[i].s >> q[i].e;
	}
	std::sort(q, q + M);
	int s = q[0].s, e = q[0].e;
	for (int i = s; i <= e; ++i) add_count(A[i]);
	answer[q[0].index] = max > (e - s + 1) / 2;
	for (int i = 1; i < M; ++i) {
		while (s < q[i].s) pop_count(A[s++]);
		while (s > q[i].s) add_count(A[--s]);
		while (e < q[i].e) add_count(A[++e]);
		while (e > q[i].e) pop_count(A[e--]);
		answer[q[i].index] = max > (e - s + 1) / 2;
	}
	for (int i = 0; i < M; ++i) std::cout << answer[i] << '\n';
}