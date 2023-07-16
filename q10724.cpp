#include <iostream>
#include <cstring>
#include <vector>

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
		void update() {
			s = 1;
			max = v;
			max_i = i;
			if (l) {
				s += l->s;
				if (l->max > max) {
					max = l->max;
					max_i = l->max_i;
				}
			}
			if (r) {
				s += r->s;
				if (r->max > max) {
					max = r->max;
					max_i = r->max_i;
				}
			}
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
		splay(x); x->r = 0;
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
	Result query(Node* x, Node* y) {
		Node* l = get_lca(x, y);
		Result result = { l->v, l->i };

		access(x); splay(l);
		if (l->r && l->r->max > result.max)
			result = { l->r->max, l->r->max_i };

		access(y); splay(l);
		if (l->r && l->r->max > result.max)
			result = { l->r->max, l->r->max_i };

		return result;
	}

	void update(Node* x, int d) {
		splay(x);
		x->v = d;
		x->update();
	}

	void make_root(int u) { make_root(&t[u]); }
	void link(int u, int v) { link(&t[u], &t[v]); }
	void cut(int u, int v) { cut(&t[u], &t[v]); }
	Result query(int u, int v) { return query(&t[u], &t[v]); }
} lct;

struct Edge { int u, v; } edges[LEN];
std::vector<Edge> graph[100'001];
void dfs(int u, int p = 0) {
	for (const Edge& e : graph[u]) {
		if (e.u == p) continue;
		dfs(e.u, u);
		lct.t[N + e.u].i = lct.t[N + e.u].max_i = N + e.u;
		lct.t[N + e.u].v = lct.t[N + e.u].max = e.v;
		lct.link(e.u, N + e.u);
		lct.link(N + e.u, u);
		edges[N + e.u] = { u, e.u };
	}
}

ll solve() {
	ll answer = 0, mst = 0;
	for (std::vector<Edge>& v : graph) v.clear();
	memset(lct.t, 0, sizeof lct.t);

	std::cin >> N >> M;
	for (int i = 2, u, c; i <= N; ++i) {
		std::cin >> u >> c; ++u;
		graph[i].push_back({ u, c });
		graph[u].push_back({ i, c });
		mst += c;
	}

	dfs(1);

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
			lct.make_root(u);
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