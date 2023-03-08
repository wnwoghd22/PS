#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

typedef unsigned int ll;
const int LEN = 500'001;

struct Node { // for seg tree
	ll v;
	ll a = 1, b; // lazy
	void push(ll a, ll b) {
		this->a = this->a * a;
		this->b = this->b * a + b;
	}
} seg_tree[LEN * 4];
int N, Q, q, X, Y, V;

void propagate(int s, int e, int i) {
	Node& n = seg_tree[i];
	if (n.a != 1 || n.b) {
		n.v = n.v * n.a + n.b * (e - s + 1);
		if (s ^ e) {
			for (int d = 0; d < 2; ++d)
				seg_tree[i << 1 | d].push(n.a, n.b);
		}
		n.a = 1;
		n.b = 0;
	}
}
void update(int l, int r, ll a, ll b, int s = 1, int e = N, int i = 1) {
	propagate(s, e, i);

	if (e < l || r < s) return;

	Node& n = seg_tree[i];
	if (l <= s && e <= r) {
		n.v = n.v * a + b * (e - s + 1);
		if (s ^ e) {
			for (int d = 0; d < 2; ++d)
				seg_tree[i << 1 | d].push(a, b);
		}
		return;
	}
	int m = s + e >> 1;
	update(l, r, a, b, s, m, i << 1);
	update(l, r, a, b, m + 1, e, i << 1 | 1);
	n.v = seg_tree[i << 1].v + seg_tree[i << 1 | 1].v;
}
ll get(int l, int r, int s = 1, int e = N, int i = 1) {
	propagate(s, e, i);

	if (e < l || r < s) return 0;
	if (l <= s && e <= r) return seg_tree[i].v;

	int m = s + e >> 1;
	return get(l, r, s, m, i << 1) + get(l, r, m + 1, e, i << 1 | 1);
}

std::vector<int> graph[LEN];
int parent[LEN], level[LEN], tree_size[LEN];
int ord, in[LEN], out[LEN], heavy[LEN];
int ch_ord, chain[LEN], chain_size[LEN], chain_top[LEN];

int dfs(int u, int p = 0) {
	tree_size[u] = 1;
	parent[u] = p;
	level[u] = level[p] + 1;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		int sub_size = dfs(v, u);
		if (!heavy[u] || sub_size > tree_size[heavy[u]]) heavy[u] = v;
		tree_size[u] += sub_size;
	}
	return tree_size[u];
}
void dfs_euler(int u, int p = 0) {
	in[u] = ++ord;
	chain[u] = ch_ord;
	if (!chain_size[chain[u]]) chain_top[chain[u]] = u;
	++chain_size[chain[u]];

	if (heavy[u]) dfs_euler(heavy[u], u);
	for (const int& v : graph[u]) {
		if (v == p || v == heavy[u]) continue;
		++ch_ord;
		dfs_euler(v, u);
	}
	out[u] = ord;
}

void q1(int x, ll v) { update(in[x], out[x], 1, v); }
void q2(int x, int y, ll v) {
	while (chain[x] ^ chain[y]) {
		if (level[chain_top[chain[x]]] > level[chain_top[chain[y]]]) std::swap(x, y);
		update(in[chain_top[chain[y]]], in[y], 1, v);
		y = parent[chain_top[chain[y]]];
	}
	if (level[x] > level[y]) std::swap(x, y);
	update(in[x], in[y], 1, v);
}
void q3(int x, ll v) { update(in[x], out[x], v, 0); }
void q4(int x, int y, ll v) {
	while (chain[x] ^ chain[y]) {
		if (level[chain_top[chain[x]]] > level[chain_top[chain[y]]]) std::swap(x, y);
		update(in[chain_top[chain[y]]], in[y], v, 0);
		y = parent[chain_top[chain[y]]];
	}
	if (level[x] > level[y]) std::swap(x, y);
	update(in[x], in[y], v, 0);
}
ll q5(int x) { return get(in[x], out[x]); }
ll q6(int x, int y) {
	ll result = 0;
	while (chain[x] ^ chain[y]) {
		if (level[chain_top[chain[x]]] > level[chain_top[chain[y]]]) std::swap(x, y);
		result += get(in[chain_top[chain[y]]], in[y]);
		y = parent[chain_top[chain[y]]];
	}
	if (level[x] > level[y]) std::swap(x, y);
	result += get(in[x], in[y]);

	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> Q;
	for (int i = 1; i < N; ++i) {
		std::cin >> X >> Y;
		graph[X].push_back(Y);
		graph[Y].push_back(X);
	}
	dfs(1);
	dfs_euler(1);
	while (Q--) {
		std::cin >> q;
		if (q == 1) std::cin >> X >> V, q1(X, V);
		else if (q == 2) std::cin >> X >> Y >> V, q2(X, Y, V);
		else if (q == 3) std::cin >> X >> V, q3(X, V);
		else if (q == 4) std::cin >> X >> Y >> V, q4(X, Y, V);
		else if (q == 5) std::cin >> X, std::cout << q5(X) << '\n';
		else if (q == 6) std::cin >> X >> Y, std::cout << q6(X, Y) << '\n';
	}
}