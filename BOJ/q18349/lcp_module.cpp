#include "lcp_module.h"

const int CNT = 88'889;
const int S_LEN = 202'021;
const int SZ = CNT + S_LEN + 10;
const int BKT = 512;

int str_len, SA[SZ], t, g[SZ], tg[SZ], RANK[SZ];
std::vector<int> LCP;

// points
int cnt = 0, long_id[CNT], idx[SZ];
std::vector<int> points[CNT];
int cache[BKT][BKT];

SparseTable rmq;

void SparseTable::build(const std::vector<int>& a) {
	n = (int)a.size();
	if (n == 0) return;
	lg.assign(n + 1, 0);
	for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
	int K = lg[n] + 1;
	st.assign(K, std::vector<int>(n));
	st[0] = a;
	for (int k = 1; k < K; ++k) {
		int len = 1 << (k - 1);
		for (int i = 0; i + (1 << k) <= n; ++i) {
			st[k][i] = std::min(st[k - 1][i], st[k - 1][i + len]);
		}
	}
}
int SparseTable::query(int l, int r) const { // [l, r)
	if (l >= r) return INT_MAX;
	int len = r - l;
	int k = lg[len];
	return std::min(st[k][l], st[k][r - (1 << k)]);
}

bool compare(int x, int y) { return g[x] == g[y] ? g[x + t] < g[y + t] : g[x] < g[y]; }
void manber_myers(const std::string& s) {
	t = 1;
	str_len = s.length();
	for (int i = 0; i < str_len; ++i) {
		SA[i] = i; g[i] = s[i] - 'a';
	}
	g[str_len] = -256;
	while (t <= str_len) {
		std::sort(SA, SA + str_len, compare);
		tg[SA[0]] = 0;

		for (int i = 1; i < str_len; ++i) {
			if (compare(SA[i - 1], SA[i])) tg[SA[i]] = tg[SA[i - 1]] + 1;
			else tg[SA[i]] = tg[SA[i - 1]];
		}
		for (int i = 0; i < str_len; ++i) g[i] = tg[i];

		t <<= 1;
	}
}
void get_lcp(const std::string& s) {
	LCP.resize(str_len + 10);
	for (int i = 0; i < str_len; ++i) RANK[SA[i]] = i;
	int len = 0;
	for (int i = 0, j; i < str_len; ++i) {
		int k = RANK[i];
		if (k) {
			j = SA[k - 1];
			while (s[i + len] != '#' && 
			 	s[j + len] != '#' &&
			 	s[i + len] == s[j + len]) ++len;
			LCP[k] = len;
			if (len) --len;
		}
	}
}

void preprocess(const std::vector<std::string>& data) {
	std::string S = "";
	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			idx[S.size() + j] = i + 1;
		}
		if (data[i].length() > BKT) long_id[i + 1] = cnt;
		else long_id[i + 1] = -1;

		S += data[i] + "#";
	}
	manber_myers(S);
	get_lcp(S);

	rmq = SparseTable(LCP);
	memset(cache, 0, sizeof cache);
	std::vector<int> last_seen(cnt, -1);

	for (int k = 0, i, j; k < (int)S.length(); ++k) {
		j = SA[k];
		if (S[j] == '#') continue;
		i = idx[j];
		points[i].push_back(k);
		if (long_id[i] == -1) continue; // short string
		int lid = long_id[i];

		// update cache with all previously seen long strings
		for (int t = 0; t < cnt; ++t) {
			if (last_seen[t] == -1) continue;
			int L = std::min(k, last_seen[t]) + 1;
			int R = std::max(k, last_seen[t]) + 1;
			int v = rmq.query(L, R);
			if (v > cache[lid][t]) {
				cache[lid][t] = v;
				cache[t][lid] = v;
			}
		}
		last_seen[lid] = k;
	}
}

// two pointer swipping through points[i] and points[j]
int naive_query(int i, int j) {	
	const auto& A = points[i + 1];
	const auto& B = points[j + 1];

	if (A.empty() || B.empty()) return -1;

	int ans = 0;
	int pb = 0;

	auto eval_pair = [&](int l, int r) {
		if (l == r) return;
		int L = std::min(l, r) + 1;
		int R = std::max(l, r) + 1;
		int v = rmq.query(L, R);
		if (v > ans) ans = v;
		};

	for (int a : A) {
		while (pb < (int)B.size() && B[pb] < a) ++pb;
		if (pb < (int)B.size()) eval_pair(a, B[pb]);
		if (pb > 0) eval_pair(a, B[pb - 1]);
	}

	return ans;
}
int bound_query(int i, int j) {
	if (~long_id[i + 1]) std::swap(i, j);
	const auto& A = points[i + 1]; // short
	const auto& B = points[j + 1]; // long
	if (A.empty() || B.empty()) return -1;

	int ans = 0;

	auto eval_pair = [&](int l, int r) {
		if (l == r) return;
		int L = std::min(l, r) + 1;
		int R = std::max(l, r) + 1;
		int v = rmq.query(L, R);
		if (v > ans) ans = v;
		};

	for (int a : A) {
		auto it = std::lower_bound(B.begin(), B.end(), a);
		if (it != B.end()) eval_pair(a, *it);
		if (it != B.begin()) {
			int b = *std::prev(it);
			eval_pair(a, b);
		}
	}

	return ans;
}
int cache_query(int i, int j) { return cache[long_id[i + 1]][long_id[j + 1]]; }

int C(int i, int j) {
	if (!~long_id[i + 1] && !~long_id[j + 1]) return naive_query(i, j);
	if (~long_id[i + 1] && ~long_id[j + 1]) return cache_query(i, j);
	return bound_query(i, j);
}
