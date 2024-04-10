#include <iostream>

typedef long long ll;
const int LEN = 100'001;

int N, M;

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
	int get_lca(int u, int v) { return get_lca(&t[u], &t[v])->v; }
} lct;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);

	std::cin >> N >> M;
	for (int u = 1; u <= N; ++u) lct.t[u].v = u;
	for (int i = 0, q, u, v; i < M; ++i) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> u >> v;
			lct.link(u, v);
		}
		if (q == 2) {
			std::cin >> v;
			lct.cut(v);
		}
		if (q == 3) {
			std::cin >> u >> v;
			std::cout << lct.get_lca(u, v) << '\n';
		}
	}
}