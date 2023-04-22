#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class SplayTree {
	struct Node {
		Node* l;
		Node* r;
		Node* p;
		int size;
		char c;
		Node(char c = 0) : l(0), r(0), p(0), size(1), c(c) {}
		~Node() { if (l) delete l; if (r) delete r; }
		void update() {
			size = 1;
			if (l) size += l->size;
			if (r) size += r->size;
		}
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
	void clear() { if (root) delete root; root = 0; }
	~SplayTree() { clear(); }
	void init(char* s) {
		if (root) clear();
		root = new Node;
		Node* cur = root;
		for (int i = 0; s[i]; ++i) {
			cur->r = new Node(s[i]);
			cur->r->p = cur;
			cur = cur->r;
		}
		Node* tail = new Node;
		cur->r = tail;
		tail->p = cur;
		splay(tail);
	}
	void get(int i) {
		Node* p = root;
		while (1) {
			while (p->l && p->l->size > i) p = p->l;
			if (p->l) i -= p->l->size;
			if (!i--) break;
			p = p->r;
		}
		splay(p);
	}
	void insert(int i, char* s) {
		for (int j = 0; s[j]; ++j) {
			get(i + j);
			Node* l = root, * r = root->r;
			Node* m = new Node(s[j]);
			m->r = r; r->p = m;
			l->r = m; m->p = l;
			m->update(); l->update();
		}
	}
	void print(int x, int y) {
		for (int i = x + 1; i <= y + 1; ++i) {
			get(i);
			std::cout << root->c;
		}
		std::cout << '\n';
	}
} sp;

char S[1'000'001];

int main() {
	freopen("input.txt", "r", stdin);
	int T, X, Y;
	std::cin >> T;
	while (T--) {
		std::cin >> S;
		sp.init(S);
		while (1) {
			std::cin >> S;
			if (S[0] == 'I') {
				std::cin >> S >> X;
				sp.insert(X, S);
			}
			else if (S[0] == 'P') {
				std::cin >> X >> Y;
				sp.print(X, Y);
			}
			else if (S[0] == 'E') break;
		}
	}
}