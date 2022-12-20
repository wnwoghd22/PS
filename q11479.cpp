#include <iostream>
#include <algorithm>

const int LEN = 1'000'001;
int N, SA[LEN], LCP[LEN], t, g[LEN], tg[LEN], RANK[LEN];

bool compare(int x, int y) { return g[x] == g[y] ? g[x + t] < g[y + t] : g[x] < g[y]; }
void manber_myers(const std::string& s) {
	t = 1;
	N = s.length();
	for (int i = 0; i < N; ++i) {
		SA[i] = i; g[i] = s[i] - 'a';
	}
	while (t <= N) {
		g[N] = -1;
		std::sort(SA, SA + N, compare);
		tg[SA[0]] = 0;

		for (int i = 1; i < N; ++i) {
			if (compare(SA[i - 1], SA[i])) tg[SA[i]] = tg[SA[i - 1]] + 1;
			else tg[SA[i]] = tg[SA[i - 1]];
		}
		for (int i = 0; i < N; ++i) g[i] = tg[i];

		t <<= 1;
	}
}
void get_lcp(std::string s) {
	for (int i = 0; i < N; ++i) RANK[SA[i]] = i;
	int len = 0;
	for (int i = 0, j; i < N; ++i) {
		int k = RANK[i];
		if (k) {
			j = SA[k - 1];
			while (s[i + len] == s[j + len]) ++len;
			LCP[k] = len;
			if (len) --len;
		}
	}
}

int main() {
	std::string S;
	std::cin >> S;
	manber_myers(S);
	get_lcp(S);
	long long result = (long long) N * (N + 1) / 2;
	for (int i = 1; i < N; ++i) result -= LCP[i];
	std::cout << result;
}