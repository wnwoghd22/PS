#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 200'001;

int N, M, Q;

struct LinkCutTreeL {
	struct Node {
		Node* l, * r, * p;
		int s; // size
		bool f; // flip
		int v, i;
		void update() {
			s = 1;
			if (l) s += l->s;
			if (r) s += r->s;
		}
		bool is_root() { return !p || (p->l != this && p->r != this); }
		bool is_left() { return p->l == this; }
		void rotate() {
			if (is_left()) r && (r->p = p), p->l = r, r = p;
			else l && (l->p = p), p->r = l, l = p;

			if (!p->is_root()) (p->is_left() ? p->p->l : p->p->r) = this;
			Node* y = p; p = y->p; y->p = this;
			y->update(); update();
		}
		void push() {
			if (f) {
				if (l) l->f ^= 1;
				if (r) r->f ^= 1;
				std::swap(l, r);
				f = 0;
			}
		}
	} t[LEN];
	void splay(Node* x) {
		for (Node* p; !x->is_root(); x->rotate()) {
			p = x->p;
			if (!p->is_root()) p->p->push(); p->push(); x->push();
			if (p->is_root()) continue;	// zig
			if (x->is_left() == p->is_left()) p->rotate();	// zig-zig
			else x->rotate();	// zig-zag
		}
		x->push();
	}
	void access(Node* x) {
		splay(x); x->r = 0; x->update();
		for (; x->p; splay(x))
			splay(x->p), x->p->r = x;
	}
	void make_root(Node* x) {
		access(x);
		x->f ^= 1;
	}
	void link(Node* x, Node* p) {
		access(x);
		access(p);
		p->p = x; x->l = p;
		x->update();
	}
	void cut(Node* x) {
		access(x);
		if (!x->l) return;
		x->l = x->l->p = 0;
		x->update();
	}
	Node* get_root(Node* x) {
		access(x);
		while (x->l) x = x->l, x->push();
		splay(x);
		return x;
	}
	Node* get_parent(Node* x) {
		access(x);
		if (!x->l) return 0;
		x = x->l; x->push();
		while (x->r) x = x->r, x->push();
		splay(x);
		return x;
	}
	void cut(Node* x, Node* y) {
		if (get_parent(x) == y) cut(x);
		else cut(y);
	}
	int get_depth(Node* x) {
		access(x);
		return x->l ? x->l->s : 0;
	}
	Node* get_lca(Node* x, Node* y) {
		access(x); access(y); splay(x);
		return x->p ? x->p : x;
	}
	void update(Node* x, int d) {
		splay(x);
		x->v = d;
		x->update();
	}

	Node* get_root(int u) { return get_root(&t[u]); }
	void make_root(int u) { make_root(&t[u]); }
	void link(int u, int v) { link(&t[u], &t[v]); }
	void cut(int u, int v) { cut(&t[u], &t[v]); }
	void cut(int u) { cut(&t[u]); }
} lct;

std::vector<int> graph[LEN];
bool available[LEN];
struct Edge { int u, v; } edges[LEN];
int val[LEN];
int parent[LEN];
void dfs(int u, int p = 0) {
	for (const int& v : graph[u]) {
		if (v == p) continue;
		parent[v] = u;
		dfs(v, u);
	}
}

void link(int i) {
	int u = edges[i].u;
	int v = edges[i].v;
	if (parent[u] == v) std::swap(u, v);
	lct.get_root(u)->v += lct.t[v].v - val[i];
	lct.link(v, u);
}
void cut(int i) {
	int u = edges[i].u;
	int v = edges[i].v;
	val[i] = lct.get_root(u)->v;
	lct.t[u].v = lct.t[v].v = val[i];
	if (parent[v] == u) lct.cut(v);
	else lct.cut(u);
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);

	std::cin >> N >> M >> Q;
	for (int i = 1; i <= N; ++i) lct.t[i].i = i, lct.t[i].v = lct.t[i].s = 1;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		edges[i].u = u, edges[i].v = v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs(1);

	for (int i = 0, d; i < M; ++i) {
		std::cin >> d;
		if (!available[d]) link(d);
		else cut(d);
		available[d] ^= 1;
	}

	for (int i = 0, c; i < Q; ++i) {
		std::cin >> c;
		std::cout << lct.get_root(c)->v << '\n';
	}
}