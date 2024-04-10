#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 200'001;

int N, C, Q;
int c[LEN], cc[LEN];

struct LinkCutTree {
	struct Node {
		Node* l, * r, * p;
		int s; // size
		int i;
		int c, lazy;
		void update() {
			s = 1;
			if (l) s += l->s;
			if (r) s += r->s;
		}
		bool is_root() { return !p || (p->l != this && p->r != this); }
		bool is_left() { return p->l == this; }
		int chain_size() { return 1 + (l ? l->s : 0); }
		void rotate() {
			if (is_left()) r && (r->p = p), p->l = r, r = p;
			else l && (l->p = p), p->r = l, l = p;

			if (!p->is_root()) (p->is_left() ? p->p->l : p->p->r) = this;
			Node* y = p; p = y->p; y->p = this;
			y->update(); update();
		}
		void push() {
			if (lazy) {
				c = lazy;
				if (l) l->lazy = lazy;
				if (r) r->lazy = lazy;
				lazy = 0;
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
	void set_color(int u, int v) {
		Node* x = &t[u];

		splay(x); x->r = 0; x->update();
		if (x->c) {
			--cc[c[x->c]];
			// std::cout << "erase " << x->c << ' ' << x->chain_size() - (x->p == 0) << '\n';
			c[x->c] -= x->chain_size() - (x->p == 0);
			// std::cout << "count of color " << x->c << " = " << c[x->c] << '\n';
			++cc[c[x->c]];
		}
		for (; x->p; splay(x)) {
			splay(x->p);

			if (x->p->c) {
				--cc[c[x->p->c]];
				// std::cout << "erase " << x->p->c << ' ' << x->p->chain_size() - (x->p->p == 0) << '\n';
				c[x->p->c] -= x->p->chain_size() - (x->p->p == 0);
				// std::cout << "count of color " << x->p->c << " = " << c[x->p->c] << '\n';
				++cc[c[x->p->c]];
			}

			x->p->r = x;
		}
		--cc[c[v]];
		x->lazy = v;
		// std::cout << "color " << v << ' ' << x->chain_size() << '\n';
		c[v] += x->s - 1;
		++cc[c[v]];
	}
	void link_fast(int u, int p) {
		t[p].r = &t[u];
		t[u].p = &t[p];
		t[u].update();
		t[p].update();
	}
} lct;

std::vector<int> graph[LEN];
void dfs(int u, int p = 0) {
	lct.t[u].i = u;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		dfs(v, u);
		lct.link_fast(v, u);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);

	std::cin >> N >> C >> Q;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs(1);
	cc[0] = C;

	for (int i = 0, u, c, m; i < Q; ++i) {
		std::cin >> u >> c >> m;
		lct.set_color(u, c);
		std::cout << cc[m] << '\n';
	}
}