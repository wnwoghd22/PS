#include <iostream>
#include <cstring>

const int LEN = 300'000;
int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	if (a > b) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return true;
}

class SplayTree {
	struct Node {
		Node* l, * r, * p;
		int key, size;
		bool flip;
		Node() : l(0), r(0), p(0), key(0), size(0), flip(0) {}
		~Node() { if (l) delete l; if (r) delete r; }
		void propagate() {
			if (flip) {
				std::swap(l, r);
				if (l) l->flip ^= 1;
				if (r) r->flip ^= 1;
				flip = 0;
			}
		}
		void update() {
			size = 1;
			if (l) size += l->size;
			if (r) size += r->size;
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
		for (int i = 1; i <= LEN; ++i) {
			cur->r = new Node;
			cur->r->p = cur;
			cur = cur->r;
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
		return p->key;
	}
	void flip(int s, int e) {
		Node* x = gather(s, e);
		x->flip ^= 1;
	}
	void insert(int k, int s, int e) {
		if (s ^ e) {
			flip(s, e);
			flip(s + 1, e);
		}
		get(s);
		root->key = k;
	}
} sp;

int N, M, L, W = -1;

int main() {
	std::cin >> N >> M;
	memset(p, -1, sizeof p);
	sp.init();
	for (int k = 1; k <= N; ++k) {
		std::cin >> L;
		int e = find(L);
		sp.insert(k, L, e);
		join(e, e + 1);
		W = std::max(W, find(e) - 1);
	}
	std::cout << W << '\n';
	for (int i = 1; i <= W; ++i) std::cout << sp.get(i) << ' ';
}