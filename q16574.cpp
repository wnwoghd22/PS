#include <iostream>
#include <vector>

const int LEN = 100'001;

int N;
std::vector<int> graph[LEN];
int p[LEN];
int ord, order[LEN], level[LEN];
int heavy[LEN], size[LEN];
int ch_ord, chain[LEN], chain_top[LEN];
bool on_board[LEN];

struct SegTree {
	int t[LEN << 2];
	void update(int l, int r, int d, int s = 1, int e = N, int i = 1) {
		if (r < s || e < l) return;
		if (l <= s && e <= r) { t[i] += d; return; }
		int m = s + e >> 1;
		update(l, r, d, s, m, i << 1);
		update(l, r, d, m + 1, e, i << 1 | 1);
	}
	int get(int x, int s = 1, int e = N, int i = 1) {
		if (e < x || x < s) return 0;
		if (s == e) return t[i];
		int m = s + e >> 1;
		return t[i] + get(x, s, m, i << 1) + get(x, m + 1, e, i << 1 | 1);
	}
} even, odd;

struct LinkCutTree {
	struct Node {
		Node* l, * r, * p;
		int v;
		bool is_root() { return !p || (p->l != this && p->r != this); }
		bool is_left() { return p->l == this; }
		void rotate() {
			if (is_left()) r && (r->p = p), p->l = r, r = p;
			else l && (l->p = p), p->r = l, l = p;

			if (!p->is_root()) (p->is_left() ? p->p->l : p->p->r) = this;
			Node* y = p; p = y->p; y->p = this;
		}
	} t[LEN];
	void splay(Node* x) {
		for (Node* p; !x->is_root(); x->rotate()) {
			p = x->p;
			if (p->is_root()) continue;	// zig
			if (x->is_left() == p->is_left()) p->rotate();	// zig-zig
			else x->rotate();	// zig-zag
		}
	}
	void access(Node* x) {
		splay(x); x->r = 0;
		for (; x->p; splay(x))
			splay(x->p), x->p->r = x;
	}
	void link(Node* x, Node* p) {
		access(x);
		access(p);
		p->p = x; x->l = p;
	}
	void cut(Node* x) {
		access(x);
		if (!x->l) return;
		x->l = x->l->p = 0;
	}
	Node* get_root(Node* x) {
		access(x);
		while (x->l) x = x->l;
		splay(x);
		return x;
	}
	Node* get_parent(Node* x) {
		access(x);
		if (!x->l) return 0;
		x = x->l;
		while (x->r) x = x->r;
		splay(x);
		return x;
	}
	Node* get_lca(Node* x, Node* y) {
		access(x); access(y); splay(x);
		return x->p ? x->p : x;
	}
	void cut(int v) { cut(&t[v]); }
	void link(int u, int v) { link(&t[u], &t[v]); }
} lct;

int dfs(int u, int p = 0) {

}

void dfs_euler(int u, int p) {

}