#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>

const int LEN = 300'001;

int N, C, M, sqrtN, A[LEN], answer[LEN], count[LEN], max = 0;
std::set<int> buckets[LEN];

void add_count(int n) {
	if (count[n] == max) ++max;
	buckets[count[n]++].erase(n);
	buckets[count[n]].insert(n);
}

void pop_count(int n) {
	if (count[n] == max && buckets[count[n]].size() == 1) --max;
	buckets[count[n]--].erase(n);
	buckets[count[n]].insert(n);
}

struct Query {
	int index, s, e;
	bool operator<(const Query& r) { return s / sqrtN ^ r.s / sqrtN ? s / sqrtN < r.s / sqrtN : e < r.e; }
} q[LEN];

int main() {
	std::cin >> N >> C;
	sqrtN = sqrt(N);
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	for (int i = 1; i <= C; ++i) buckets[0].insert(i);
	std::cin >> M;
	for (int i = 0; i < M; ++i) {
		q[i].index = i;
		std::cin >> q[i].s >> q[i].e;
	}
	std::sort(q, q + M);
	int s = q[0].s, e = q[0].e;
	for (int i = s; i <= e; ++i) add_count(A[i]);
	answer[q[0].index] = max > (e - s + 1) / 2 ? *buckets[max].begin() : -1;
	for (int i = 1; i < M; ++i) {
		while (s < q[i].s) pop_count(A[s++]);
		while (s > q[i].s) add_count(A[--s]);
		while (e < q[i].e) add_count(A[++e]);
		while (e > q[i].e) pop_count(A[e--]);
		answer[q[i].index] = max > (e - s + 1) / 2 ? *buckets[max].begin() : -1;
	}
	for (int i = 0; i < M; ++i)
		if (~answer[i]) std::cout << "yes " << answer[i] << '\n';
		else std::cout << "no\n";
}