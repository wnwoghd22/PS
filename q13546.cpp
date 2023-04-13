#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

const int LEN = 100'001;

int N, sqN, K, Q, A[LEN], ans[LEN];
int order[LEN], bucket[LEN], cnt[LEN], temp[LEN];
int next[LEN], before[LEN], l[LEN], r[LEN];
void push(int k) { 
	// std::cout << "push " << k << ' ' << k / sqN << '\n'; 
	++cnt[k]; ++bucket[k / sqN];
}
void pop(int k) { 
	// std::cout << "pop " << k << ' ' << k / sqN << '\n';
	--cnt[k]; --bucket[k / sqN];
}
int get_max() {
	// std::cout << "search: ";
	for (int i = N / sqN; i >= 0; --i) {
		if (bucket[i]) {
			// std::cout << "bucket " << i << ' ';
			for (int j = std::min((i + 1) * sqN, N) - 1; j >= i * sqN; --j) {
				// std::cout << j << ' ';
				if (cnt[j])
					return j;
			}
		}
	}
	return 0;
}

void counting_sort() {
	memset(cnt, 0, sizeof cnt);
	for (int i = 0; i < N; ++i) ++cnt[A[i]];
	for (int k = 2; k <= K; ++k) cnt[k] += cnt[k - 1];
	for (int i = N - 1; i >= 0; --i) order[--cnt[A[i]]] = i;
}
struct Query {
	int i, s, e;
	bool operator<(const Query& r) const {
		int le = e / sqN, re = r.e / sqN;
		return le == re ? s < r.s : le < re;
	}
} q[LEN];
void merge(int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) temp[k++] = q[order[i]] < q[order[j]] ? order[i++] : order[j++];
	while (i <= m) temp[k++] = order[i++];
	while (j <= r) temp[k++] = order[j++];
	for (i = l; i <= r; ++i) order[i] = temp[i];
}
void merge_sort(int l, int r) {
	if (l == r) return;
	int m = l + r >> 1;
	merge_sort(l, m);
	merge_sort(m + 1, r);
	merge(l, m, r);
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> K;
	sqN = sqrt(N);
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	counting_sort(); 
	for (int i = 0; i < N - 1; ++i)
		next[order[i]] = A[order[i]] == A[order[i + 1]] ? order[i + 1] : N;
	next[order[N - 1]] = N;
	for (int i = N - 1; i > 0; --i)
		before[order[i]] = A[order[i]] == A[order[i - 1]] ? order[i - 1] : -1;
	before[order[0]] = -1;

	// std::cout << "sqrt N: " << sqN << '\n';
	// for (int i = 0; i < N; ++i) std::cout << A[i] << ' '; std::cout << '\n';
	// for (int i = 0; i < N; ++i) std::cout << order[i] << ' '; std::cout << '\n';
	// for (int i = 0; i < N; ++i) std::cout << A[order[i]] << ' '; std::cout << '\n';
	// for (int i = 0; i < N; ++i) std::cout << next[i] << ' '; std::cout << '\n';
	// for (int i = 0; i < N; ++i) std::cout << before[i] << ' '; std::cout << '\n';

	std::cin >> Q;
	for (int i = 0; i < Q; ++i) {
		q[i].i = order[i] = i;
		std::cin >> q[i].s >> q[i].e;
		--q[i].s; --q[i].e;
	}
	merge_sort(0, Q - 1);
	memset(cnt, 0, sizeof cnt);
	memset(l, -1, sizeof l);
	memset(r, -1, sizeof r);

	l[A[0]] = r[A[0]] = 0;
	cnt[0] = bucket[0] = 1;
	for (int i = 0, s = 0, e = 0; i < Q; ++i) {
		const Query& c = q[order[i]];
		// std::cout << "query: " << c.s << ' ' << c.e << ' ' << c.i << '\n';
		// std::cout << "<-s\n";
		for (int j = s - 1; j >= c.s; --j) {
			// std::cout << A[j] << " l: " << l[A[j]] << ", r: " << r[A[j]] << '\n';
			if (!~l[A[j]]) {
				l[A[j]] = r[A[j]] = j;
				push(0);
				continue;
			}
			pop(r[A[j]] - l[A[j]]);
			l[A[j]] = j;
			push(r[A[j]] - l[A[j]]);
		}
		// std::cout << "e->\n";
		for (int j = e + 1; j <= c.e; ++j) {
			// std::cout << A[j] << " l: " << l[A[j]] << ", r: " << r[A[j]] << '\n';
			if (!~l[A[j]]) {
				l[A[j]] = r[A[j]] = j;
				push(0);
				continue;
			}
			pop(r[A[j]] - l[A[j]]);
			r[A[j]] = j;
			push(r[A[j]] - l[A[j]]);
		}
		// std::cout << "s->\n";
		for (int j = s; j < c.s; ++j) {
			// std::cout << A[j] << " l: " << l[A[j]] << ", r: " << r[A[j]] << '\n';
			if (next[j] > std::max(c.e, e)) {
				// std::cout << "delete " << A[j] << ' ' << next[j] << ' ' << e << '\n';
				pop(0);
				l[A[j]] = r[A[j]] = -1;
				continue;
			}
			pop(r[A[j]] - l[A[j]]);
			l[A[j]] = next[j];
			push(r[A[j]] - l[A[j]]);
		}
		// std::cout << "<-e\n";
		for (int j = e; j > c.e; --j) {
			// std::cout << A[j] << " l: " << l[A[j]] << ", r: " << r[A[j]] << '\n';
			if (before[j] < std::min(c.s, s)) {
				pop(0);
				l[A[j]] = r[A[j]] = -1;
				continue;
			}
			pop(r[A[j]] - l[A[j]]);
			r[A[j]] = before[j];
			push(r[A[j]] - l[A[j]]);
		}
		s = c.s;
		e = c.e;
		ans[c.i] = get_max();
	}
	for (int i = 0; i < Q; ++i) std::cout << ans[i] << '\n';
}