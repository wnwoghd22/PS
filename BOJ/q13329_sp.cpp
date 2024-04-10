#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 100'001;

struct Pos {
	ll x, y;
	int idx, d;
	bool operator<(const Pos& r) const { return y * r.x > r.y * x; }
} cur, pos[LEN << 1];

ll cross(const Pos& d1, const Pos& d2, const Pos& d3, const Pos& d4) { return (d2.x - d1.x) * (d4.y - d3.y) - (d2.y - d1.y) * (d4.x - d3.x); }

struct Segment {
	Pos l, r;
	int idx;
	bool operator<(const Segment& rhs) const {
		if (l < rhs.l) return cross(r, l, l, rhs.l) < 0;
		else return cross(rhs.r, rhs.l, rhs.l, l) > 0;
	}
} segments[LEN];

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
			if (segments[i] < segments[p->i]) {
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
	}
	bool find(int i) {
		if (!root) return 0;
		Node* p = root;
		while (1) {
			if (p->i == i) break;
			if (segments[i] < segments[p->i]) {
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

int N, M, K, checked[LEN];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		segments[i].idx = i;
		std::cin >> M >> segments[i].l.x >> segments[i].l.y;
		segments[i].r = segments[i].l;
		for (int j = 1; j < M; ++j) {
			std::cin >> cur.x >> cur.y;
			if (cur < segments[i].l) segments[i].l = cur;
			if (segments[i].r < cur) segments[i].r = cur;
		}
		pos[i << 1] = segments[i].l; pos[i << 1].d = 1; pos[i << 1].idx = i;
		pos[i << 1 | 1] = segments[i].r; pos[i << 1 | 1].d = -1; pos[i << 1 | 1].idx = i;
	}
	std::sort(pos, pos + N * 2);

	for (int i = 0; i < N * 2; ++i) {
		if (~pos[i].d) s.insert(pos[i].idx);
		else s.pop(pos[i].idx);
		int top = s.top();
		if (~top) K += !checked[top]++;
	}
	std::cout << N - K;
}