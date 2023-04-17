#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 200'001;
int N, cnt[LEN], ord[LEN], SA[LEN], g[LEN], tg[LEN];
int lcp[LEN], rank[LEN];
char S[LEN];

inline int min(int x, int y) { return x < y ? x : y; }
inline bool compare(int x, int y, int t) { return g[x] == g[y] ? g[x + t] < g[y + t] : g[x] < g[y]; }
void manber_myers(const int n, const char* s) {
	for (int i = 0; i < n; ++i) SA[i] = i, g[i] = s[i];
	for (int t = 1; t < n; t <<= 1) {
		// radix sort by rank(i + 2^t)
		memset(cnt, 0, sizeof cnt);
		for (int i = 0; i < n; ++i) ++cnt[g[min(i + t, n)]];
		for (int i = 1; i < LEN; ++i) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i) ord[--cnt[g[min(i + t, n)]]] = i;

		// radix sort by rank(i)
		memset(cnt, 0, sizeof cnt);
		for (int i = 0; i < n; ++i) ++cnt[g[i]];
		for (int i = 1; i < LEN; ++i) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i) SA[--cnt[g[ord[i]]]] = ord[i];

		tg[SA[0]] = 1;
		for (int i = 1; i < n; ++i)
			tg[SA[i]] = tg[SA[i - 1]] + compare(SA[i - 1], SA[i], t);
		for (int i = 0; i < n; ++i) g[i] = tg[i];
	}
}

void get_lcp(const int n, const char* s) {
	for (int i = 0; i < n; ++i) rank[SA[i]] = i;
	int len = 0;
	for (int i = 0, j, k; i < n; ++i) {
		if (k = rank[i]) {
			j = SA[k - 1];
			while (s[i + len] == s[j + len]) ++len;
			lcp[k] = len;
			if (len) --len;
		}
	}
}

int main() {
	std::cin >> S;
	N = strlen(S);
	manber_myers(N, S);
	get_lcp(N, S);
	for (int i = 0; i < N; ++i) {
		printf("%s\n", S + SA[i]);
	}
	for (int i = 1; i < N; ++i) std::cout << lcp[i] << ' ';
}