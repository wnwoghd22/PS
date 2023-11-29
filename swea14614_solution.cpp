#include <iostream>
#include <stack>

const int LEN = 101;

class SplayTree {
public:
	struct Node {
		Node* l;
		Node* r;
		Node* p;
		int val, dir;
		int size;
		Node(int val, int dir) : l(0), r(0), p(0), val(val), dir(dir), size(1) {}
		~Node() {
			if (l) delete l;
			if (r) delete r;
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
	SplayTree() : root(0) {}
	// ~SplayTree() { if (root) delete root; }
	void clear() { if (root) delete root; }
	int size() { return root ? root->size : 0; }
	void insert(int val, int dir) {
		if (!root) {
			root = new Node(val, dir);
			return;
		}
		Node* p = root;
		Node** pp;
		while (1) {
			if (p->val == val) return;
			if (p->val > val) {
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
		Node* x = new Node(val, dir);
		x->p = p;
		*pp = x;
		splay(x);
	}
	bool find(int val) {
		if (!root) return false;
		Node* p = root;
		while (1) {
			if (p->val == val) break;
			if (p->val > val) {
				if (!p->l) break;
				p = p->l;
			}
			else {
				if (!p->r) break;
				p = p->r;
			}
		}
		splay(p);
		return p->val == val;
	}
	void pop(int val) {
		if (!find(val)) return;
		Node* p = root;

		if (p->l && p->r) {
			root = p->l; root->p = 0;
			Node* l = root;
			while (l->r) l = l->r;
			l->r = p->r;
			p->r->p = l;
			l->update();
			splay(l);
		}
		else if (p->l) root = p->l, root->p = 0;
		else if (p->r) root = p->r, root->p = 0;
		else root = 0;
		p->l = 0;
		p->r = 0;

		delete p;
		p = 0;
	}
	Node* get(int i) {
		Node* p = root;
		if (!p) return 0;
		if (p->size <= i) return 0;
		while (1) {
			while (p->l && p->l->size > i) p = p->l;
			if (p->l) i -= p->l->size;
			if (!i--) break;
			p = p->r;
		}
		splay(p);
		return p;
	}
	Node* left_bound(int val) {
		find(val);
		if (root->val > val) {
			Node* cur = root->l;
			while (cur->r) cur = cur->r;
			splay(cur);
		}
		return root;
	}
} st[LEN];

void init() {
	for (int i = 1; i <= 100; ++i) {
		st[i].clear();
		st[i].insert(0, 0);
	}
}

void add(int mX, int mY) {
	st[mX].insert(mY, 1);
	st[mX + 1].insert(mY, -1);
}

void remove(int mX, int mY) {
	st[mX].pop(mY);
	st[mX + 1].pop(mY);
}

int numOfCross(int mID) {
	int x = mID;
	int y = 0;
	int cross = 0;
	while (1) {
		st[x].find(y);
		int idx = st[x].root->l ? st[x].root->l->size : 0;
		SplayTree::Node* next = st[x].get(idx + 1);
		if (!next) break;
		x += next->dir;
		y = next->val;
		cross++;
	}
	return cross;
}

int participant(int mX, int mY) {
	int x = mX;
	int y = mY;
	SplayTree::Node* cur = st[x].left_bound(y);
	while (cur->val) {
		x += cur->dir;
		st[x].find(y);
		int idx = st[x].root->l ? st[x].root->l->size : 0; // never be 0
		cur = st[x].get(idx - 1);
		y = cur->val;
	}
	return x;
}