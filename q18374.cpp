#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>

typedef long long ll;
const int LEN = 200'001;

int N, Q;

struct LinkCutTree {
	struct Node {
		Node* l, * r, * p;
		int s; // size
		int f;
		ll v, sum;
		void update() {
			s = 1;
			sum = v;
			if (l) s += l->s, sum += l->sum;
			if (r) s += r->s, sum += r->sum;
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
		splay(x); x->r = 0, x->update();
		for (; x->p; splay(x))
			splay(x->p), x->p->r = x;
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

	void update(Node* x, ll d) {
		splay(x);
		x->v = d;
		x->update();
	}

	void link(int u, int v) { link(&t[u], &t[v]); }
	void cut(int u, int v) { cut(&t[u], &t[v]); }

	void q1(int i, int j) {
		if (t[i].f == j) return;
		Node* head = get_root(&t[i]);
		if (t[i].f != i) {
			Node* tail = &t[head->f];
			Node* l = get_lca(&t[i], tail);
			cut(&t[i]);
			if (l == &t[i]) // cut cycle and make root
				link(head, tail);
		}

		head = get_root(&t[j]);
		t[i].f = j;
		if (head != &t[i])
			link(i, j);
	}
	void q2(int i, ll x) { update(&t[i], x); }
	ll q3(int x) {
		ll result = 0;
		Node* head = get_root(&t[x]);
		access(head);
		Node* tail = &t[head->f];
		access(tail);
		splay(&t[x]);
		if (t[x].p) {
			result += tail->sum;
			// std::cout << "cycle sum: " << result << '\n';
			access(t[x].p);
			splay(&t[x]);
		}
		// std::cout << "chain sum: " << t[x].sum << '\n';
		result += t[x].sum;
		
		return result;
	}
} lct;

int visited[LEN];
std::vector<int> graph[LEN];
void dfs(int u, int color) {
	visited[u] = color;
	for (const int& v : graph[u]) {
		if (visited[v]) {
			if (visited[v] == color) continue; // cycle
			else {
				lct.link(v, u);
				return;
			}
		}
		dfs(v, color);
		lct.link(v, u);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);

	std::cin >> N >> Q;
	for (int v = 1, u; v <= N; ++v) {
		std::cin >> u;
		lct.t[v].f = u;
		graph[u].push_back(v);
	}

	for (int i = 1, a; i <= N; ++i) {
		std::cin >> a;
		lct.t[i].v = lct.t[i].sum = a;
	}

	for (int u = 1; u <= N; ++u) {
		if (!visited[u])
			dfs(u, u);
	}

	for (int q, i, j, k = 0; k < Q; ++k) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> i >> j;
			lct.q1(i, j);
		}
		if (q == 2) {
			std::cin >> i >> j;
			lct.q2(i, j);
		}
		if (q == 3) {
			std::cin >> i;
			std::cout << lct.q3(i) << '\n';
		}
	}
}