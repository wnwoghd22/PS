#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 100'001;
const int LOG = 17;
int ord, in[LEN], out[LEN], min[LEN]; // euler tour order
int level[LEN], parent[LEN][LOG + 1]; // for lca
std::vector<int> graph[LEN];
int N, E, Q;

void dfs(int u, int p = 0) { // dfs spanning tree
	in[u] = min[u] = ++ord;
	parent[u][0] = p;
	level[u] = level[p] + 1;
	for (int i = 1, v = p; v; v = parent[u][i++]) {
		parent[u][i] = parent[v][i - 1];
	}
	for (const int& v : graph[u]) {
		if (v == p) continue;
		if (!in[v]) {
			dfs(v, u);
			min[u] = std::min(min[u], min[v]);
		}
		else min[u] = std::min(min[u], in[v]);
	}
	out[u] = ord;
}
int is_ancestor(int x, int y) { return in[x] <= in[y] && out[y] <= out[x]; }

int lca(int u, int v) {
	if (level[u] ^ level[v]) {
		if (level[u] > level[v]) std::swap(u, v);
		for (int i = LOG; i >= 0; --i)
			if (level[parent[v][i]] >= level[u])
				v = parent[v][i];
	}
	int l = u;
	if (u ^ v) {
		for (int i = LOG; i >= 0; --i) {
			if (parent[u][i] ^ parent[v][i]) {
				u = parent[u][i];
				v = parent[v][i];
			}
			l = parent[u][i];
		}
	}
	return l;
}
