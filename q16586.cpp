#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

const int LEN = 100'001;

class SplayTree {
	struct Node {
		Node* l; // left
		Node* r; // right
		Node* p; // parent
		int val;
		int size;
		bool flip;
		Node(int val) : l(0), r(0), p(0), val(val), size(1), flip(0) {}
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
	} *root, *ptr[LEN];
	void rotate(Node* x) {
		Node* p = x->p;
		Node* b = 0;
		if (!p) return; // root
		p->propagate();
		x->propagate();
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
				if ((x == p->l) && (p == g->l)) rotate(p);
				else rotate(x);
			}
			rotate(x);
		}
	}
	void splay(Node* x, Node* g) {
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
	SplayTree() : root(0) { memset(ptr, 0, sizeof ptr); }
	~SplayTree() { if (root) delete root; }
	void init(int n) {
		if (root) delete root;
		root = new Node(-1);
		Node* cur = root;
		for (int i = 1; i <= n; ++i) {
			ptr[i] = cur->r = new Node(i);
			cur->r->p = cur;
			cur = cur->r;
		}
		cur->r = new Node(-1);
		cur->r->p = cur;
		splay(ptr[n / 2 + 1]);
	}
	int get(int i) {
		Node* x = root;
		if (!x) return -1;
		x->propagate();
		while (1) {
			while (x->l && x->l->size > i) x = x->l, x->propagate();
			if (x->l) i -= x->l->size;
			if (!i--) break;
			x = x->r;
			x->propagate();
		}
		splay(x);
		return x->val;
	}
	void flip(int s, int e) {
		Node* x = gather(s, e);
		x->flip ^= 1;
	}
	int index_of(int v) {
		splay(ptr[v]);
		return root->l->size;
	}
	int slide(int a, int b) {
		int idx_a = index_of(a);
		int idx_b = index_of(b);
		if (idx_a < idx_b) {
			flip(idx_a, idx_b);
			flip(idx_a, idx_b - 1);
			return idx_b - idx_a;
		}
		else {
			if (idx_a - idx_b == 1) return 0;
			flip(idx_b + 1, idx_a);
			flip(idx_b + 2, idx_a);
			return idx_b - idx_a + 1;
		}
	}
} st;

int main() {
	freopen("input.txt", "r", stdin);
	int N, Q, A, B;
	std::cin >> N >> Q;
	st.init(N);
	while (Q--) {
		std::cin >> A >> B;
		std::cout << st.slide(A, B) << '\n';
	}
	for (int i = 1; i <= N; ++i)
		std::cout << st.get(i) << ' ';
}