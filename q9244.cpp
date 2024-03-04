#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long ll;
const int LEN = 100'001;

struct Pos {
	ll x, y;
	bool operator<(const Pos& p) const { return x == p.x ? y < p.y : x < p.x; }
	friend std::istream& operator>>(std::istream& is, Pos& p) { is >> p.x >> p.y; return is; }
};
ll cross(const Pos& p1, const Pos& p2, const Pos& p3) { return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x); }

struct Segment {
	Pos l, r;
	bool operator<(const Segment& rhs) const {
		if (l < rhs.l) return cross(r, l, rhs.l) < 0;
		else return cross(rhs.r, rhs.l, l) > 0;
	}
} seg[LEN];

struct Query {
	Pos p;
	int idx, d;
	bool operator<(const Query& q) const { 
		if (p.x == q.p.x) {
			if (d == q.d) {
				if (d == 1) return p.y < q.p.y;
				return p.y > q.p.y;
			}
			return d > q.d;
		}
		return p.x < q.p.x;
	}
} queries[LEN << 1];

int par[LEN];

class SplayTree {
	struct Node {
		int i;
		Node* l;
		Node* r;
		Node* p;
		Node(int i) : i(i), l(0), r(0), p(0) {}
		~Node() { if (l) delete l; if (r) delete r; }
	} *root;
	void rotate(Node* x) {
		Node* p = x->p;
		if (!p) return;
		Node* b = 0;
		if (x == p->l) {
			p->l = b = x->r;
			x->r = p;
		}
		else {
			p->r = b = x->l;
			x->l = p;
		}
		x->p = p->p;
		p->p = x;
		if (b) b->p = p;
		(x->p ? p == x->p->l ? x->p->l : x->p->r : root) = x;
	}
	void splay(Node* x) {
		while (x->p) {
			Node* p = x->p;
			Node* g = p->p;
			if (g) {
				if ((x == p->l) == (p == g->l)) rotate(p);
				else rotate(x);
			}
			rotate(x);
		}
	}
public:
	SplayTree() : root(0) {}
	~SplayTree() { if (root) delete root; }
	void insert(int i) {
		if (!root) {
			root = new Node(i);
			return;
		}
		Node* p = root;
		Node** pp;
		while (1) {
			if (p->i == i) return;
			if (seg[i] < seg[p->i]) {
				if (!p->l) {
					pp = &p->l;
					break;
				}
				p = p->l;
			}
			else {
				if (!p->r) {
					pp = &p->r;
					break;
				}
				p = p->r;
			}
		}
		Node* x = new Node(i);
		x->p = p;
		*pp = x;
		splay(x);

		if (seg[i].l.y < seg[i].r.y) {
			if (root->l) {
				Node* l = root->l;
				while (l->r) l = l->r;
				par[i] = l->i;
			}
			else par[i] = -1;
		}
	}
	bool find(int i) {
		if (!root) return 0;
		Node* p = root;
		while (1) {
			if (p->i == i) break;
			if (seg[i] < seg[p->i]) {
				if (!p->l) break;
				p = p->l;
			}
			else {
				if (!p->r) break;
				p = p->r;
			}
		}
		splay(p);
		return p->i == i;
	}
	void pop(int i) {
		if (!find(i)) return;

		if (seg[i].r.y < seg[i].l.y) {
			if (root->l) {
				Node* l = root->l;
				while (l->r) l = l->r;
				par[i] = l->i;
			}
			else par[i] = -1;
		}

		Node* p = root;

		if (p->l && p->r) {
			root = p->l; root->p = 0;
			Node* l = root;
			while (l->r) l = l->r;
			l->r = p->r;
			p->r->p = l;
		}
		else if (p->l) root = p->l, root->p = 0;
		else if (p->r) root = p->r, root->p = 0;
		else root = 0;
		p->l = p->r = 0;
		delete p;
	}
	int top() {
		if (!root) return -1;
		Node* p = root;
		while (p->l) p = p->l;
		splay(p);
		return p->i;
	}
} s;

int N, x, idx = -1;
bool check(int i) {
	if (!~idx) return 1;
	ll y0 = seg[idx].l.y;
	ll dx0 = seg[idx].r.x - seg[idx].l.x;
	ll dy0 = seg[idx].r.y - seg[idx].l.y;
	ll px0 = x - seg[idx].l.x;
	ll y1 = seg[i].l.y;
	ll dx1 = seg[i].r.x - seg[i].l.x;
	ll dy1 = seg[i].r.y - seg[i].l.y;
	ll px1 = x - seg[i].l.x;

	// y1 + dy1 * (px1 / dx1) > y0 + dy0 * (px0 / dx0)
	// dx0, dx1 > 0
	// 
	// (y1 * dx1 * dx0) + (dy1 * px1 * dx0) > (y0 * dx1 * dx0) + (dy0 * px0 * dx1)
	// return y1 * dx1 * dx0 + dy1 * px1 * dx0 > y0 * dx1 * dx0 + dy0 * px0 * dx1;

	return y1 + dy1 * (double)(px1 / dx1) > y0 + dy0 * (double)(px0 / dx0);
}

int main() {
	freopen("input.txt", "r", stdin);

	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> seg[i].l >> seg[i].r;
		if (seg[i].l.x > seg[i].r.x) std::swap(seg[i].l, seg[i].r);
		queries[i << 1] = { seg[i].l, i, 1 };
		queries[i << 1 | 1] = { seg[i].r, i, -1 };
	}
	std::cin >> x;
	std::sort(queries, queries + N * 2);
	memset(par, -1, sizeof par);
	for (int i = 0; i < N * 2; ++i) {
		if (~queries[i].d) s.insert(queries[i].idx);
		else s.pop(queries[i].idx);
	}

	// for (int i = 0; i < N; ++i) 
	// 	std::cout << par[i] << ' ';
	// std::cout << '\n';

	for (int i = 0; i < N; ++i) {
		if (x >= seg[i].l.x && x <= seg[i].r.x && check(i)) 
			idx = i;
	}
	// std::cout << idx << '\n';
	if (!~idx) std::cout << x;
	else {
		while (~par[idx]) idx = par[idx];
		// std::cout << idx << '\n';
		std::cout << (seg[idx].l.y < seg[idx].r.y ? seg[idx].l.x : seg[idx].r.x);
	}
}