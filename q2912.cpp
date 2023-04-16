#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>

const int LEN = 300'001;

int N, C, M, sqrtN, A[LEN], answer[LEN], count[LEN], bucket[LEN], max = 0;
char buckets[100][LEN], bucket_max[100];

void add_count(int n) {
	if (count[n] == max) ++max;
	int bi = (n - 1) / 100;
	if (bucket_max[bi] == count[n]) ++bucket_max[bi];
	--buckets[bi][count[n]]; --bucket[count[n]]; ++count[n];
	++buckets[bi][count[n]]; ++bucket[count[n]];
}

void pop_count(int n) {
	int bi = (n - 1) / 100;
	if (count[n] == max && bucket[count[n]] == 1) --max;
	if (count[n] == bucket_max[bi] && buckets[bi][count[n]] == 1) --bucket_max[bi];
	--buckets[bi][count[n]]; --bucket[count[n]]; --count[n];
	++buckets[bi][count[n]]; ++bucket[count[n]];
}
int get_max(int k) {
	std::cout << k << '\n';
	if (max <= k) return -1;
	for (int i = 99; i >= 0; --i) {
		std::cout << "bucket: " << i << '\n';
		if (bucket_max[i] > k) {
			for (int j = (i + 1) * 100; j > i * 100; --j) {
				if (count[j] > k)
					return j;
			}
		}
	}
	return -1;
}

struct Query {
	int index, s, e;
	bool operator<(const Query& r) { return s / sqrtN ^ r.s / sqrtN ? s / sqrtN < r.s / sqrtN : e < r.e; }
} q[LEN];

int main() {
	std::cin >> N >> C;
	sqrtN = sqrt(N);
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	for (int i = 0; i < 100; ++i) buckets[i][0] = 100;
	bucket[0] = C;
	std::cin >> M;
	for (int i = 0; i < M; ++i) {
		q[i].index = i;
		std::cin >> q[i].s >> q[i].e;
	}
	std::sort(q, q + M);
	int s = q[0].s, e = q[0].e;
	for (int i = s; i <= e; ++i) add_count(A[i]);
	answer[q[0].index] = get_max(e - s + 1 >> 1);
	for (int i = 1; i < M; ++i) {
		while (s > q[i].s) add_count(A[--s]);
		while (e < q[i].e) add_count(A[++e]);
		while (s < q[i].s) pop_count(A[s++]);
		while (e > q[i].e) pop_count(A[e--]);
		answer[q[i].index] = get_max(e - s + 1 >> 1);
	}
	for (int i = 0; i < M; ++i)
		if (~answer[i]) std::cout << "yes " << answer[i] << '\n';
		else std::cout << "no\n";
}