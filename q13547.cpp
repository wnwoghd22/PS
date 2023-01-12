#include <iostream>
#include <cmath>
#include <algorithm>

const int LEN = 100'001;
const int MAX = 1'000'001;

int N, M, sqrtN, A[LEN], answer[LEN], count[MAX], S;
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
		if (!count[A[i]]++) ++S;
	}
	answer[q[0].index] = S;
	for (int i = 1; i < M; ++i) {
		while (s < q[i].s) if (!--count[A[s++]]) --S;
		while (s > q[i].s) if (!count[A[--s]]++) ++S;
		while (e < q[i].e) if (!count[A[++e]]++) ++S;
		while (e > q[i].e) if (!--count[A[e--]]) --S;
		answer[q[i].index] = S;
	}
	for (int i = 0; i < M; ++i) std::cout << answer[i] << '\n';
}