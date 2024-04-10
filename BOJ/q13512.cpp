#include <iostream>
#include <vector>

const int LEN = 100'001;
const int INF = 1e9;

int N;

int seg_min[LEN << 2];
void update(int x, int d, int s = 1, int e = N, int i = 1) {
	if (e < x && x < s) return;
	if (s == e) { seg_min[x] = d; return; }
	int m = s + e >> 1;
	update(x, d, s, m, i << 1); update(x, d, m + 1, e, i << 1 | 1);
	seg_min[i] = std::min(seg_min[i << 1], seg_min[i << 1 | 1]);
}

int get_min(int l, int r, int s = 1, int e = N, int i = 1) {
	if (e < l || r < s) return INF;
	if (l <= s && e <= r) return seg_min[i];
	int m = s + e >> 1;
	return std::min(get_min(l, r, s, m, i << 1), get_min(l, r, m + 1, e, i << 1 | 1));
}

std::vector<int> graph[LEN];
int level[LEN], size[LEN], parent[LEN];
int ord, order[LEN], heavy[LEN];
int ch_ord, chain[LEN], ch_top[LEN];

int dfs(int u, int p = 0) {
	level[u] = level[p] + 1;
	size[u] = 1;
	
	for (const int& v : graph[u]) {
		if (v == p) continue;
		int sub = dfs(v, u);
		if (!heavy[u] || sub > size[heavy[u]]) 
			heavy[u] = v;
		size[u] += sub;
	}
	return size[u];
}

void dfs_euler(int u, int p = 0) {
	order[u] = ++ord;
	chain[u] = ch_ord;

}

int main() {

}