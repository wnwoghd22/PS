#include <iostream>
#include <cstring>

typedef long long ll;
const int LEN = 300'001;

int T, N, M;

struct Result { int max, max_i; };

struct LinkCutTree {
	struct Node {
		Node* l, *r, *p;
		int s; // size
		bool f; // flip
		int v, i, max, max_i;
	} t[LEN];
	void update(Node* x) {
		x->s = 1;
		x->max = x->v;
		x->max_i = x->i;
		if (x->l) {
			x->s += x->l->s;
			if (x->l->max > x->max) {
				x->max = x->l->max;
				x->max_i = x->l->max_i;
			}
		}
		if (x->r) {
			x->s += x->r->s;
			if (x->r->max > x->max) {
				x->max = x->r->max;
				x->max_i = x->r->max_i;
			}
		}
	}
	bool is_root(Node* x) { return !x->p || (x->p->l != x && x->p->r != x); }
	bool is_left(Node* x) { return x->p->l == x; }
	void rotate(Node* x) {
		Node* p = x->p;
		if (is_left(x)) {
			if (x->r) x->r->p = p;
			p->l = x->r; x->r = p;
		}
		else {
			if (x->l) x->l->p = p;
			p->r = x->l; x->l = p;
		}
		if (!is_root(p)) (is_left(p) ? p->p->l : p->p->r) = x;
		x->p = p->p; p->p = x;
		update(p); update(x);
	}
	void push(Node* x) {
		if (x->f) {
			if (x->l) x->l->f ^= 1;
			if (x->r) x->r->f ^= 1;
			std::swap(x->l, x->r);
			x->f = 0;
		}
	}
	void splay(Node* x) {
		for (Node* p; !is_root(x); rotate(x)) {
			p = x->p;
			if (!is_root(p)) push(p->p);
			push(p); push(x);
			if (is_root(p)) continue;	// zig
			if (is_left(x) == is_left(p)) rotate(p);	// zig-zig
			else rotate(x);	// zig-zag
		}
		push(x);
	}
	void access(Node* x) {
		splay(x); x->r = 0;
		for (Node* p; x->p; splay(x)) {
			p = x->p;
			splay(p); p->r = x;
		}
	}
	void make_root(Node* x) {
		access(x);
		x->f ^= 1;
	}
	void link(Node* x, Node* p) {
		make_root(x); push(x);
		access(p);
		p->p = x; x->l = p;
	}
	void cut(Node* x) {
		access(x);
		// if (!x->l) return;
		x->l->p = 0;
		x->l = 0;
	}
	Node* get_root(Node* x) {
		access(x);
		while (x->l) x = x->l, push(x);
		splay(x);
		return x;
	}
	Node* get_parent(Node* x) {
		access(x);
		if (!x->l) return 0;
		x = x->l; push(x);
		while (x->r) x = x->r, push(x);
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
	Result query(Node* x, Node* y) {
		Node* l = get_lca(x, y);
		Result result = { l->max, l->max_i };

		access(x); splay(l);
		if (l->r) {
			if (l->r->max > result.max) {
				result.max = l->r->max;
				result.max_i = l->r->max_i;
			}
		}

		access(y); splay(l);
		if (l->r) {
			if (l->r->max > result.max) {
				result.max = l->r->max;
				result.max_i = l->r->max_i;
			}
		}

		return result;
	}

	void update(Node* x, int d) {
		splay(x);
		x->v = d;
		update(x);
	}

	void link(int u, int v) { link(&t[u], &t[v]); }
	void cut(int u, int v) { cut(&t[u], &t[v]); }
	Result query(int u, int v) { return query(&t[u], &t[v]); }
} lct;

struct Edge { int u, v; } edges[LEN];

ll solve() {
	ll answer = 0, mst = 0;
	memset(lct.t, 0, sizeof lct.t);

	std::cin >> N >> M;
	for (int i = 2, u, c; i <= N; ++i) {
		std::cin >> u >> c; ++u;
		lct.t[N + i].i = lct.t[N + i].max_i = N + i;
		lct.t[N + i].v = lct.t[N + i].max = c;
		lct.link(i, N + i);
		lct.link(N + i, u);
		edges[N + i] = { i, u };
		mst += c;
	}

	for (int j = 1, u, v, c; j <= M; ++j) {
		std::cin >> u >> v >> c; ++u, ++v;
		if (u == v) {
			answer ^= mst;
			continue;
		}
		lct.t[N * 2 + j].i = lct.t[N * 2 + j].max_i = N * 2 + j;
		lct.t[N * 2 + j].v = lct.t[N * 2 + j].max = c;
		edges[N * 2 + j] = { u, v };

		Result cur = lct.query(u, v);
		if (c < cur.max) {
			mst += c - cur.max;
			lct.cut(edges[cur.max_i].u, cur.max_i);
			lct.cut(edges[cur.max_i].v, cur.max_i);
			lct.link(u, N * 2 + j);
			lct.link(N * 2 + j, v);
		}
		// std::cout << mst << '\n';
		answer ^= mst;
	}
	return answer;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--)
		std::cout << solve() << '\n';
}