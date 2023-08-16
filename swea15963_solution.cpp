#include <algorithm>
#include <cstring>
#include <iostream>

const int LEN = 200'001;

class SplayTree {
public:
	struct Node {
		Node* l, * r, * p;
		int size;
		int val, min, max;
		Node() : l(0), r(0), p(0), size(0), val(0), min(0), max(0) {}
		void update() {
			size = 1;
			min = max = val;
			if (l) {
				size += l->size;
				min = std::min(min, l->min);
				max = std::max(max, l->max);
			}
			if (r) {
				size += r->size;
				min = std::min(min, r->min);
				max = std::max(max, r->max);
			}
		}
	} *root, nodes[LEN];
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
	int sp;
	SplayTree() : root(0), sp(0) {}
	void init(int n, int* arr) {
		// std::cout << "init " << n << "\n";
		memset(nodes, 0, sizeof nodes);
		sp = 0;
		root = &nodes[sp++]; // dummy
		Node* cur = root;
		cur->size = 1;
		for (int i = 0; i < n; ++i) {
			cur->r = &nodes[sp++];
			cur->r->p = cur;
			cur = cur->r;
			cur->min = cur->max = cur->val = arr[i];
			cur->size = 1;
			// std::cout << "put arr[" << i << "] = " << cur->val << '\n';
		}
		cur->r = &nodes[sp++]; // dummy
		cur->r->p = cur;
		cur->r->size = 1;
		splay(cur);
	}
	int get(int i) {
		Node* p = root;
		if (!p) return -1;
		while (1) {
			while (p->l && p->l->size > i) p = p->l;
			if (p->l) i -= p->l->size;
			if (!i--) break;
			p = p->r;
		}
		splay(p);
		return p->val;
	}
	void add(int m, int* mValue) {
		// std::cout << "add\n";
		int len = root->size;
		Node* cur = gather(1, len - 2);
		// std::cout << cur->size << '\n';
		Node * head, * tail;
		head = &nodes[sp++];
		head->max = head->min = head->val = mValue[0];
		head->size = 1;
		head->l = cur;
		cur->p = head;
		root->r->l = head;
		head->p = root->r;
		head->update(); root->r->update(); root->update();
		tail = head;
		for (int i = 1; i < m; ++i) {
			tail->r = &nodes[sp++];
			tail->r->p = tail;
			tail = tail->r;
			tail->max = tail->min = tail->val = mValue[i];
			tail->size = 1;
		}
		splay(tail);
	}
	void erase(int from, int to) {
		gather(from, to);
		root->r->l = 0;
		root->r->update();
		root->update();
	}
	int find(int k) {
		int len = root->size;
		// std::cout << "find\n";
		// std::cout << root->val << ' ' << len << '\n';
		Node* x = gather(len - k - 1, len - 2);
		return x->max - x->min;
	}
} sp;

void init(int N, int mValue[]) {
	sp.init(N, mValue);
}

void add(int M, int mValue[]) {
	sp.add(M, mValue);
}

void erase(int mFrom, int mTo) {
	sp.erase(mFrom, mTo);
}

int find(int K) {
	return sp.find(K);
}