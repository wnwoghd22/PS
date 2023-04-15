#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const int LEN = 100'001;

int N;

struct Node {
	ll lm, rm, sum, max;
	bool lazy;	// for lazy
	ll val;	// for lazy
	Node operator+(const Node& r) const {
		return {
			std::max(lm, sum + r.rm),
			std::max(rm + r.sum, r.rm),
			sum + r.sum,
			std::max({ max, r.max, rm + r.lm })
		};
	}
} seg_tree[LEN * 4];

void propagate(int s, int e, int i) {
	if (seg_tree[i].lazy) {
		seg_tree[i].sum = seg_tree[i].val * (e - s + 1);
		seg_tree[i].lm = seg_tree[i].rm = seg_tree[i].max = std::max(seg_tree[i].sum, 0ll);
		if (s ^ e) {
			for (int j = 0; j < 2; ++j) {
				seg_tree[i << 1 | j].lazy = 1;
				seg_tree[i << 1 | j].val = seg_tree[i].val;
			}
		}
		seg_tree[i].lazy = 0;
	}
}

void update(int l, int r, ll d, int s = 1, int e = N, int i = 1) {
	propagate(s, e, i);
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		seg_tree[i].sum = d * (e - s + 1);
		if (s ^ e) {
			for (int j = 0; j < 2; ++j) {
				seg_tree[i << 1 | j].lazy = 1;
				seg_tree[i << 1 | j].val = d;
			}
		}
		return;
	}
	int m = s + e >> 1;
	update(l, r, d, s, m, i << 1);
	update(l, r, d, m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] + seg_tree[i << 1 | 1];
}

Node get(int l, int r, int s = 1, int e = N, int i = 1) {
	propagate(s, e, i);
	if (e < l || r < s) return { 0, 0, 0, 0 };
	if (l <= s && e <= r) return seg_tree[i];
	int m = s + e >> 1;
	return get(l, r, s, m, i << 1) + get(l, r, m + 1, e, i << 1 | 1);
}

std::vector<int> graph[LEN];
int parent[LEN][20], level[LEN], size[LEN];
int ord, order[LEN], heavy[LEN];
int ch_ord, chain[LEN], chain_size[LEN], chain_top[LEN];

int dfs(int u, int p = 0) {
	level[u] = level[p] + 1;
	parent[u][0] = p;
	
}

void dfs_euler(int u, int p = 0) {

}

int lca(int u, int v) {

}

ll query1(int u, int v) {
	if (order[u] > order[v]) std::swap(u, v);
	int l = lca(u, v);
	Node total = { 0, 0, 0, 0 };

}

ll query2(int u, int v) {

}