#include <iostream>
#include <cstring>
#include <vector>

const int LEN = 1e5 + 1;

int N, M;

bool t[LEN << 2];
void update(int x, bool b, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) { t[i] = b; return; }
	int m = s + e >> 1;
	update(x, b, s, m, i << 1);
	update(x, b, m + 1, e, i << 1 | 1);
	t[i] = t[i << 1] || t[i << 1 | 1];
}
bool get(int l, int r, int s = 1, int e = N, int i = 1) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) return t[i];
	int m = s + e >> 1;
	return get(l, r, s, m, i << 1) || get(l, r, m + 1, e, i << 1 | 1);
}

std::vector<int> graph[LEN];
int pt[LEN], sz[LEN], lv[LEN];
int ord, o[LEN], hv[LEN];
int ch, c[LEN], ct[LEN];

int dfs(int u, int p = 0) {
	pt[u] = p;
	lv[u] = lv[p] + 1;
	sz[u] = 1;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		int s = dfs(v, u);
		if (!hv[u] || s > sz[hv[u]]) hv[u] = v;
		sz[u] += s;
	}
	return sz[u];
}
void dfs_euler(int u, int p = 0) {
	o[u] = ++ord;
	c[u] = ch;
	if (!ct[ch]) ct[ch] = u;
	if (hv[u]) dfs_euler(hv[u], u);
	for (const int& v : graph[u]) {
		if (v == p || v == hv[u]) continue;
		++ch;
		dfs_euler(v, u);
	}
}

bool query(int u, int v) {
	bool b = 0;
	while (c[u] ^ c[v]) {
		if (lv[ct[c[u]]] > lv[ct[c[v]]]) std::swap(u, v);
		b |= get(o[ct[c[v]]], o[v]);
		v = pt[ct[c[v]]];
	}
	if (lv[u] > lv[v]) std::swap(u, v);
	b |= get(o[u], o[v]);
	return b;
}

int cnt[LEN];
int T[LEN], Ti[LEN];
int A[LEN], B[LEN], C[LEN], Qi[LEN];
bool ans[LEN];

int main() {
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		std::cin >> T[i];
		++cnt[T[i]];
	}
	for (int i = 1; i <= N; ++i) cnt[i] += cnt[i - 1];
	for (int i = N; i; --i) Ti[cnt[T[i]]--] = i;

	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs(1);
	dfs_euler(1);

	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= M; ++i) {
		std::cin >> A[i] >> B[i] >> C[i];
		++cnt[C[i]];
	}
	for (int i = 1; i <= N; ++i) cnt[i] += cnt[i - 1];
	for (int i = M; i; --i) Qi[cnt[C[i]]--] = i;

	std::vector<int> stack;
	for (int i = 1, j = 1, k = 1; k <= N; ++k) {
		while (i <= N && T[Ti[i]] == k) {
			update(o[Ti[i]], 1);
			stack.push_back(o[Ti[i]]);
			++i;
		}
		while (j <= M && C[Qi[j]] == k) {
			ans[Qi[j]] = query(A[Qi[j]], B[Qi[j]]);
			++j;
		}
		while (stack.size()) {
			update(stack.back(), 0);
			stack.pop_back();
		}
	}
	for (int i = 1; i <= M; ++i) std::cout << ans[i];
}