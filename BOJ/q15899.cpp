#include <iostream>
#include <vector>

const int LEN = 200'001;
const int MOD = 1e9 + 7;
int N, M, C, A[LEN], tree[20][LEN];

std::vector<int> g[LEN];
int s[LEN], e[LEN], x[LEN];
int order = 0;
void dfs(int v) {
	s[v] = ++order;
	for (const int& u : g[v]) {
		if (!s[u]) dfs(u);
	}
	e[v] = order;
	x[s[v]] = v;
}

void merge(int d, int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) tree[d][k++] = tree[d + 1][i] < tree[d + 1][j] ? tree[d + 1][i++] : tree[d + 1][j++];
	while (i <= m) tree[d][k++] = tree[d + 1][i++];
	while (j <= r) tree[d][k++] = tree[d + 1][j++];
}
void merge_sort(int d, int l, int r) {
	if (l == r) tree[d][l] = A[x[l + 1]];
	else {
		int m = l + r >> 1;
		merge_sort(d + 1, l, m);
		merge_sort(d + 1, m + 1, r);
		merge(d, l, m, r);
	}
}
int upper_bound(int k, int s, int e, int d) {
	int l = s, r = e + 1, m;
	while (l < r) {
		m = l + r >> 1;
		if (tree[d][m] > k) r = m;
		else l = m + 1;
	}
	return r;
}

int query(int l, int r, int k, int s = 0, int e = N - 1, int d = 0) {
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) return upper_bound(k, s, e, d) - s;
	int m = s + e >> 1;
	return query(l, r, k, s, m, d + 1) + query(l, r, k, m + 1, e, d + 1);
}

int f(int v, int c) { return query(s[v] - 1, e[v] - 1, c); }

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M >> C;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1);
	merge_sort(0, 0, N - 1);
	
	int ret = 0;
	for (int m = 0, v, c; m < M; ++m) {
		std::cin >> v >> c;
		ret = (ret + f(v, c)) % MOD;
	}
	std::cout << ret;
}