#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cmath>

const int LEN = 100'201;
int N, M, K, sqN, bktN;

int A[LEN], S[LEN], O[LEN], before[LEN], next[LEN];
int bucket[LEN], dist[LEN], head[LEN], tail[LEN];

void merge(int l, int m, int r) {
	int i = l, j = m + 1, k = i;
	while (i <= m && j <= r) A[k++] = S[O[i]] <= S[O[j]] ? O[i++] : O[j++];
	while (i <= m) A[k++] = O[i++];
	while (j <= r) A[k++] = O[j++];
	for (i = l; i <= r; ++i) O[i] = A[i];
}
void merge_sort(int l, int r) {
	if (l == r) return;
	int m = l + r >> 1;
	merge_sort(l, m);
	merge_sort(m + 1, r);
	merge(l, m, r);
}
inline int get_max() {
	for (int i = bktN; i >= 0; --i) {
		std::cout << "bucket: " << i << '\n';
		if (bucket[i]) {
			int l = sqN * i, r = sqN * (i + 1);
			for (int j = r; j >= l; --j) {
				std::cout << "index: " << j << '\n';
				if (dist[j]) {
					return j;
				}
			}
		}
	}
	return 0;
}

struct Query {
	int s, e, i;
	bool operator<(const Query& r) const {
		int le = e / sqN, re = r.e / sqN;
		if (le == re) return s < r.s;
		return le < re;
	}
} q[LEN];

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> K;
	sqN = sqrt(N); bktN = N / sqN;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	for (int i = 1; i <= N; ++i)
		O[i] = i, S[i] = (S[i - 1] + A[i]) % K;
	merge_sort(0, N);
	A[O[0]] = 0;
	for (int i = 1, j = 0; i <= N; ++i) {	// compress
		if (S[O[i - 1]] ^ S[O[i]]) ++j;
		A[O[i]] = j;
	}
	for (int i = 0; i < N; ++i)
		next[O[i]] = A[O[i]] == A[O[i + 1]] ? O[i + 1] : N + 1;
	next[O[N]] = N + 1;
	for (int i = N; i > 0; --i)
		before[O[i]] = A[O[i]] == A[O[i - 1]] ? O[i - 1] : -1;
	before[O[0]] = -1;

	for (int i = 0; i <= N; ++i) std::cout << S[i] << ' '; std::cout << '\n';
	for (int i = 0; i <= N; ++i) std::cout << A[i] << ' '; std::cout << '\n';
	for (int i = 0; i <= N; ++i) std::cout << next[i] << ' '; std::cout << '\n';
	for (int i = 0; i <= N; ++i) std::cout << before[i] << ' '; std::cout << '\n';

	std::cin >> M;
	for (int i = 0; i < M; ++i) {
		std::cin >> q[i].s >> q[i].e;
		q[i].s--;
		q[i].i = i;
	}
	std::sort(q, q + M);
	memset(head, -1, sizeof head);
	memset(tail, -1, sizeof tail);

	head[A[0]] = tail[A[0]] = 0;
	dist[0] = bucket[0] = 1;
	for (int i = 0, s = 0, e = 0; i < M; ++i) {
		int qs = q[i].s, qe = q[i].e;
		std::cout << "query: " << qs << "~" << qe << '\n';
		while (s > qs) {
			--s;
			if (~head[A[s]]) {
				std::cout << "pop s << " << s << " , range: " << head[A[s]] << "~" << tail[A[s]] << " " << tail[A[s]] - head[A[s]] << '\n';
				--dist[tail[A[s]] - head[A[s]]];
				--bucket[(tail[A[s]] - head[A[s]]) / sqN];
				head[A[s]] = s;
			}
			else head[A[s]] = tail[A[s]] = s;
			++dist[tail[A[s]] - head[A[s]]];
			++bucket[(tail[A[s]] - head[A[s]]) / sqN]; 
			std::cout << "push s << " << s << " , range: " << head[A[s]] << "~" << tail[A[s]] << " " << tail[A[s]] - head[A[s]] << '\n';
		}
		while (e < qe) {
			++e;
			if (~head[A[e]]) {
				--dist[tail[A[e]] - head[A[e]]];
				--bucket[(tail[A[e]] - head[A[e]]) / sqN];
				std::cout << "pop e >> " << tail[A[e]] - head[A[e]] << '\n';
				tail[A[e]] = e;
			}
			else head[A[e]] = tail[A[e]] = e;
			++dist[tail[A[e]] - head[A[e]]];
			++bucket[(tail[A[e]] - head[A[e]]) / sqN]; 
			std::cout << "push e >> " << e << " , range[" << A[e] << "]: " << head[A[e]] << "~" << tail[A[e]] << " " << tail[A[e]] - head[A[e]] << '\n';
		}
		while (s < qs) {
			--dist[tail[A[s]] - head[A[s]]];
			--bucket[(tail[A[s]] - head[A[s]]) / sqN];
			std::cout << "pop s >> " << s << " , range: " << head[A[s]] << "~" << tail[A[s]] << " " << tail[A[s]] - head[A[s]] << '\n';
			if (next[s] <= tail[A[s]]) {
				head[A[s]] = next[s];
				++dist[tail[A[s]] - head[A[s]]];
				++bucket[(tail[A[s]] - head[A[s]]) / sqN];
				std::cout << "push s >> " << s << " , range: " << head[A[s]] << "~" << tail[A[s]] << " " << tail[A[s]] - head[A[s]] << '\n';
			}
			else head[A[s]] = tail[A[s]] = -1;
			++s;
		}
		while (e > qe) {
			--dist[tail[A[e]] - head[A[e]]];
			--bucket[(tail[A[e]] - head[A[e]]) / sqN];
			std::cout << "pop e << " << tail[A[e]] - head[A[e]] << '\n';
			if (before[e] >= head[A[e]]) {
				tail[A[e]] = before[e];
				++dist[tail[A[e]] - head[A[e]]];
				++bucket[(tail[A[e]] - head[A[e]]) / sqN];
				std::cout << "push e << " << e << " , range: " << head[A[e]] << "~" << tail[A[e]] << " " << tail[A[e]] - head[A[e]] << '\n';
			}
			else head[A[e]] = tail[A[e]] = -1;
			--e;
		}
		int ans = get_max();
		O[q[i].i] = ans;
	}
	for (int i = 0; i < M; ++i) std::cout << O[i] << '\n';
}