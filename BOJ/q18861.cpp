#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <queue>

typedef long long ll;
const int N_LEN = 316'001;
const int Q_LEN = 402'001;
const int LEN = N_LEN + Q_LEN;
const int INF = 1e9 + 1;

int N, Q;

struct Result { int min, min_i; };

struct LinkCutTreeL {
	struct Node {
		Node* l, * r, * p;
		int s; // size
		bool f; // flip
		int v, i, min, min_i;
		void update() {
			s = 1;
			min = v;
			min_i = i;
			if (l) {
				s += l->s;
				if (l->min < min) {
					min = l->min;
					min_i = l->min_i;
				}
			}
			if (r) {
				s += r->s;
				if (r->min < min) {
					min = r->min;
					min_i = r->min_i;
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
	Result query(Node* x, Node* y) {
		Node* rx = get_root(x);
		Node* ry = get_root(y);
		if (rx != ry) return { 0, -1 };

		Node* l = get_lca(x, y);
		Result result = { l->v, l->i };

		access(x); splay(l);
		if (l->r && l->r->min < result.min) 
			result = { l->r->min, l->r->min_i };

		access(y); splay(l);
		if (l->r && l->r->min < result.min)
			result = { l->r->min, l->r->min_i };

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

bool alive[Q_LEN];
struct Edge { int u, v; } edges[Q_LEN];
struct Info {
	int i, d;
	bool operator<(const Info& r) const { return d > r.d; }
};
std::priority_queue<Info> pq;

int main() {
	freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);

	std::cin >> N >> Q;
	for (int i = 1; i <= N; ++i) {
		lct.t[i].v = lct.t[i].min = INF;
		lct.t[i].i = lct.t[i].min_i = i;
	}

	for (int k = 1, q, i, j, x, d; k <= Q; ++k) {
		std::cin >> q;

		if (q == 1) {
			std::cin >> i >> j >> d;
			Result r = lct.query(i, j);
			if (r.min) {
				if (r.min > d) continue;
				alive[r.min_i - N] = 0;
				lct.cut(r.min_i, edges[r.min_i - N].u);
				lct.cut(r.min_i, edges[r.min_i - N].v);
			}
			lct.t[N + k].v = lct.t[N + k].min = d;
			lct.t[N + k].i = lct.t[N + k].min_i = N + k;
			lct.make_root(i);
			lct.link(i, N + k);
			lct.link(N + k, j);
			edges[k] = { i, j };
			pq.push({ N + k, d });
			alive[k] = 1;
		}

		if (q == 2) {
			std::cin >> x;
			while (pq.size()) {
				if (pq.top().d >= x) break;
				Info m = pq.top(); pq.pop();
				if (!alive[m.i - N]) continue;
				alive[m.i - N] = 0;
				lct.cut(m.i, edges[m.i - N].u);
				lct.cut(m.i, edges[m.i - N].v);
			}
		}

		if (q == 3) {
			std::cin >> i >> j;
			Result cur = lct.query(i, j);
			std::cout << cur.min << '\n';
		}
	}
}