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
		if (!in[v]) dfs(v, u);
		min[u] = std::min(min[u], min[v]);
	}
	out[u] = ord;
}
int is_ancestor(int x, int y) { return in[x] <= in[y] && out[y] <= out[x]; }

int find_ancestor(int u, int l) { // find ancestor of level l of u 
	int v = u;
	for (int i = LOG; i >= 0; --i)
		if (level[parent[v][i]] >= l)
			v = parent[v][i];
	return v;
}
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

int q1(int a, int b, int g1, int g2) {
	if (level[g1] > level[g2]) std::swap(g1, g2);
	if (level[g2] - level[g1] != 1) return 1; // not spanning -> bypass exists
	if (min[g2] < in[g2]) return 1; // not articulation -> bypass exists
	return is_ancestor(g2, a) == is_ancestor(g2, b);
}

int q2(int a, int b, int c) {
	int fa = is_ancestor(c, a), fb = is_ancestor(c, b);
	if (!fa && !fb) return 1; // neither a nor b -> no effect
	if (fa ^ fb) {
		if (fa) return min[find_ancestor(a, level[c] + 1)] < in[c]; // a is descendant -> check bypass
		if (fb) return min[find_ancestor(b, level[c] + 1)] < in[c];
	}
	fa = find_ancestor(a, level[c] + 1);
	fb = find_ancestor(b, level[c] + 1);
	if (min[fa] < in[c] && min[fb] < in[c]) return 1; // bypass exists
	return fa == fb;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> E;
	for (int i = 0, u, v; i < E; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs(1);
	for (int i = 1; i <= N; ++i)
		std::cout << "vertex" << i << ": in[" << in[i] << "], out[" << out[i] << "], min[" << min[i] << "]\n";
	std::cin >> Q;
	for (int i = 0, q, a, b, x, y; i < Q; ++i) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> a >> b >> x >> y;
			std::cout << (q1(a, b, x, y) ? "yes\n" : "no\n");
		}
		if (q == 2) {
			std::cin >> a >> b >> x;
			std::cout << (q2(a, b, x) ? "yes\n" : "no\n");
		}
	}
}