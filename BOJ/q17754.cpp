#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>

const int LEN = 1'000'001;

int N, Q;

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
	int query(int x, int y) {
		Node* rx = get_root(&t[x]);
		Node* ry = get_root(&t[y]);
		if (rx != ry) return -1;

		return get_lca(&t[x], &t[y])->v;
	}
} lct;

int main() {
	freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);

	std::cin >> N >> Q;
	for (int i = 1; i <= N; lct.t[i++].v = i);

	for (int i = 0, t, a, b; i < Q; ++i) {
		std::cin >> t;
		if (t == 1) std::cin >> a >> b, lct.link(a, b);
		if (t == 2) std::cin >> a, lct.cut(a);
		if (t == 3) std::cin >> a >> b, std::cout << lct.query(a, b) << '\n';
	}
}