#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <algorithm>

const int LEN = 300'001;

int N, C, M, sqrtN, sqrtC, A[LEN], answer[LEN], count[LEN], bucket[LEN], bucket_max[100], max = 0;
int buckets[100][LEN];

void add_count(int n) {
	if (count[n] == max) ++max;
	int bi = (n - 1) / sqrtC;
	if (bucket_max[bi] == count[n]) ++bucket_max[bi];
	--buckets[bi][count[n]]; --bucket[count[n]]; ++count[n];
	++buckets[bi][count[n]]; ++bucket[count[n]];
}

void pop_count(int n) {
	int bi = (n - 1) / sqrtC;
	if (count[n] == max && bucket[count[n]] == 1) --max;
	if (count[n] == bucket_max[bi] && buckets[bi][count[n]] == 1) --bucket_max[bi];
	--buckets[bi][count[n]]; --bucket[count[n]]; --count[n];
	++buckets[bi][count[n]]; ++bucket[count[n]];
}
int get_max(int k) {
	// std::cout << k << '\n';
	if (max <= k) return -1;
	for (int i = 0; i < C / sqrtC; ++i) {
		// std::cout << "bucket: " << i << '\n';
		if (bucket_max[i] > k) {
			for (int j = 1; j <= sqrtC; ++j) {
				if (count[i * sqrtC + j] > k) {
					// std::cout << "found: count[" << i * 100 + j << "] = " << count[i * 100 + j] << '\n';
					return i * sqrtC + j;
				}
			}
		}
	}
	return -1;
}
int find(int k) {
	if (max <= k) return -1;
	for (int i = 1; i <= C; ++i)
		if (count[i] > k) return i;
	return -1;
}


struct Query {
	int index, s, e;
	bool operator<(const Query& r) { return s / sqrtN ^ r.s / sqrtN ? s / sqrtN < r.s / sqrtN : e < r.e; }
} q[LEN];

int main() {
	freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> C;
	sqrtN = sqrt(N);
	sqrtC = sqrt(C);
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	for (int i = 0; i < 100; ++i) buckets[i][0] = 100;
	bucket[0] = C;
	std::cin >> M;
	for (int i = 0; i < M; ++i) {
		q[i].index = i;
		std::cin >> q[i].s >> q[i].e;
	}
	std::sort(q, q + M);
	// std::cout << "query " << q[0].index << ' ' << q[0].s << ' ' << q[0].e << '\n';
	int s = q[0].s, e = q[0].e;
	for (int i = s; i <= e; ++i) add_count(A[i]);
	answer[q[0].index] = get_max(e - s + 1 >> 1);
	// answer[q[0].index] = find(e - s + 1 >> 1);
	for (int i = 1; i < M; ++i) {
		// std::cout << "query " << q[i].index << ' ' << q[i].s << ' ' << q[i].e << '\n';
		while (s > q[i].s) add_count(A[--s]);
		while (e < q[i].e) add_count(A[++e]);
		while (s < q[i].s) pop_count(A[s++]);
		while (e > q[i].e) pop_count(A[e--]);
		// std::cout << "after query: " << s << ' ' << e << ' ' << (e - s + 1 >> 1) << '\n';
		answer[q[i].index] = get_max(e - s + 1 >> 1);
		// answer[q[i].index] = find(e - s + 1 >> 1);
	}
	for (int i = 0; i < M; ++i)
		if (~answer[i]) std::cout << "yes " << answer[i] << '\n';
		else std::cout << "no\n";
}