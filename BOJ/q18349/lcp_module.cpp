#include "lcp_module.h"

const int CNT = 88'889;
const int LEN = 202'021;
const int SZ = CNT + LEN + 10;
const int BKT = 512;

int N, SA[SZ], LCP[SZ], t, g[SZ], tg[SZ], RANK[SZ];

// points
int cnt = 0, is_long[CNT], num[BKT], idx[SZ];
std::vector<int> points[CNT];
int cache[BKT][BKT], pre[BKT][SZ];

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
			while (s[ + len] != '#' && 
				s[j + len] != '#' &&
				s[i + len] == s[j + len]) ++len;
			LCP[k] = len;
			if (len) --len;
		}
	}
}

void preprocess(std::vector<std::string>& data) {
	std::string S = "";
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			idx[S.size() - 1 + j] = i + 1;
		}
		if (data[i].size() > BKT) {
			is_long[i + 1] = cnt;
			num[cnt++] = i + 1;
		}
		else is_long[i + 1] = -1;

		S += data[i] + "#";
	}
	manber_myers(S);
	get_lcp(S);

	for (int k = 0, i, j; k < S.length(); ++k) {
		j = LCP[k];
		if (S[j] == '#') continue;
		i = idx[j];
		points[i].push_back(k);
		if (!is_long[i]) continue;
		for (int l = 0; l < cnt; ++l) {

		}
	}
}

int naive_query(int i, int j) {
	
}
int bound_query(int i, int j) {

}
int cache_query(int i, int j) { return cache[is_long[i]][is_long[j]]; }

int C(int i, int j) {
	if (!~is_long[i] && !~is_long[j]) return naive_query(i, j);
	if (~is_long[i] && ~is_long[j]) return cache_query(i, j);
	return bound_query(i, j);
}