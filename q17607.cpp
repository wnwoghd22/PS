#include <iostream>
#include <cstring>

const int LEN = 100'001;

int N, A[LEN], M;

class SplayTree {
	struct Node {
		Node* l, * r, * p;
		int val;
		int lm, rm, max, full;
		int size;
		bool flip;
		Node() : val(0), l(0), r(0), p(0), lm(0), rm(0), max(0), full(0), size(0), flip(0) {}
		~Node() { if (l) delete l; if (r) delete r; }
		void propagate() {
			if (flip) {
				std::swap(l, r);
				std::swap(lm, rm);
				if (l) l->flip ^= 1;
				if (r) r->flip ^= 1;
				flip = 0;
			}
		}
		void update() {
			size = 1;
			if (l) size += l->size;
			if (r) size += r->size;
			if (l && r) {
				full = l->full & val & r->full;
				lm = (l->full & val) ? l->max + val + r->lm : l->lm;
				rm = (val & r->full) ? l->rm + val + r->max : r->rm;
				max = std::max(l->max, r->max);
				if (val) max = std::max(max, l->rm + val + r->lm);
			}
			else if (l) {
				full = l->full & val;
				lm = l->full ? l->max + val : l->lm;
				rm = val ? l->rm + val : 0;
				max = std::max(l->max, rm);
			}
			else if (r) {
				full = val & r->full;
				rm = r->full ? val + r->max : r->rm;
				lm = val ? r->lm + val : 0;
				max = std::max(r->max, lm);
			}
			else lm = rm = max = full = val;
		}
	} *root;
	void rotate(Node* x) {
		Node* p = x->p;
		if (!p) return;
		p->propagate();
		x->propagate();
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
		p->update();
		x->update();
	}
	void splay(Node* x, Node* g = 0) {
		while (x->p != g) {
			Node* p = x->p;
			if (p->p == g) {
				rotate(x);
				break;
			}
			Node* pp = p->p;
			if ((x == p->l) == (p == pp->l)) rotate(p);
			else rotate(x);
			rotate(x);
		}
		if (!g) root = x;
	}
	Node* gather(int s, int e) {
		get(e + 1);
		Node* temp = root;
		get(s - 1);
		splay(temp, root);
		return root->r->l;
	}
public:
	SplayTree() : root(0) {}
	void init() {
		if (root) delete root;
		root = new Node;
		Node* cur = root;
		for (int i = 1; i <= N; ++i) {
			cur->r = new Node;
			cur->r->p = cur;
			cur = cur->r;
			cur->val = A[i];
		}
		cur->r = new Node;
		cur->r->p = cur;
		splay(cur);
	}
	int get(int i) {
		Node* p = root;
		if (!p) return -1;
		p->propagate();
		while (1) {
			while (p->l && p->l->size > i) p = p->l, p->propagate();
			if (p->l) i -= p->l->size;
			if (!i--) break;
			p = p->r;
			p->propagate();
		}
		splay(p);
		return 1;
	}
	void flip(int s, int e) {
		Node* x = gather(s, e);
		x->flip ^= 1;
		x->propagate();
		root->r->update();
		root->update();
	}
	int query(int s, int e) { return gather(s, e)->max; }
} sp;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	sp.init();

	std::cin >> M;
	for (int i = 0, q, l, r; i < M; ++i) {
		std::cin >> q >> l >> r;
		if (q == 1) sp.flip(l, r);
		if (q == 2) std::cout << sp.query(l, r) << '\n';
	}
}