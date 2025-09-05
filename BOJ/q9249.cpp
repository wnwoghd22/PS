#include <iostream>
#include <algorithm>

const int LEN = 200'010;

std::string A, B;
int N, M, SA[LEN], LCP[LEN], t, g[LEN], tg[LEN], RANK[LEN];

int range_min(int l, int r) { /* TODO */ }

bool compare(int x, int y) { return g[x] == g[y] ? g[std::min(x + t, N)] < g[std::min(y + t, N)] : g[x] < g[y]; }
void manber_myers(const std::string& s) {
	t = 1;
	N = s.length();
	for (int i = 0; i < N; ++i) {
		SA[i] = i; g[i] = s[i] - 'a';
	}
	g[N] = -1;
	while (t <= N) {
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
void get_lcp(const std::string& s) {
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
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> A >> B;
	std::string S = A + "#" + B;
	N = S.length();

	manber_myers(S);
	get_lcp(S);

	for (int i = 1; i < N; ++i) {
		// std::cout << "suffix[" << SA[i] << "]: ";
		// for (int j = SA[i]; j < N; ++j) std::cout << S[j];
		// for (int j = 0; j < N; ++j) std::cout << S[SA[i - 1] + j];
		// std::cout << " common with ";

		for (int j = 0; j < LCP[i]; ++j) std::cout << S[SA[i - 1] + j];
		std::cout << '\n';
	}

	int ret = -1;
	int max_len = -1;
	for (int i = 1; i < N; ++i) {
		if ((SA[i] < A.length()) == (SA[i - 1] < A.length())) continue;
		if (LCP[i] > max_len) {
			ret = SA[i - 1];
			max_len = LCP[i];
		}
	}
	if (~ret) {
		std::cout << max_len << '\n';
		for (int i = 0; i < max_len; ++i) std::cout << S[ret + i];
	}
	else std::cout << "0\n\n";
}