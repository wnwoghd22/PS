#include <iostream>

class SplayTree {
	struct Node {
		Node* l;
		Node* r;
		Node* p;
		int key, size;
		Node(int key) : l(0), r(0), p(0), key(key), size(1) {}
		~Node() { if (l) delete l; if (r) delete r; }
		void update() {
			size = 1;
			if (l) size += l->size;
			if (r) size += r->size;
		}
	} *root;
	void rotate(Node* x) {
		if (!x->p) return;
		Node* p = x->p;
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
	void init() {
		root = new Node(-1);
		root->r = new Node(-1);
		root->r->p = root;
		root->update();
	}
	int get(int i) {
		Node* p = root;
		while (1) {
			while (p->l && p->l->size > i) p = p->l;
			if (p->l) i -= p->l->size;
			if (!i--) break;
			p = p->r;
		}
		splay(p);
		return root->key;
	}
	void insert(int key, int i) {
		get(i);
		Node* x = new Node(key);
		x->r = root->r;
		root->r->p = x;
		root->r = x;
		x->p = root;
		x->update();
		root->update();
	}
} sp;

int N, M;

int main() {
	std::cin >> N;
	sp.init();
	for (int i = 1; i <= N; ++i) {
		std::cin >> M;
		sp.insert(i, i - M - 1);
	}
	for (int i = 1; i <= N; ++i)
		std::cout << sp.get(i) << ' ';
}