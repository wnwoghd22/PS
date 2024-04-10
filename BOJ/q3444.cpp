#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long int ll;
const int INF = 1e9;
const int LEN = 300'002;
int N, Q, q;
ll l, r, i, x;
struct Node {
	Node* l; // left
	Node* r; // right
	Node* p; // parent
	int size; // size of subtree
	ll val;
	bool flip;
	bool dummy;
	Node(ll val) : l(0), r(0), p(0), size(1), val(val), flip(0), dummy(0) {}
	~Node() { if (l) delete l; if (r) delete r; }
};
bool comp(const Node* l, const Node* r) { return l->val < r->val; }

class SplayTree {
	Node *root, *ptr[LEN];
	void propagate(Node* x) {
		if (x->flip) {
			std::swap(x->l, x->r);
			if (x->l) x->l->flip ^= 1;
			if (x->r) x->r->flip ^= 1;
			x->flip = 0;
		}
	}
	void update(Node* x) {
		x->size = 1;
		if (x->l) x->size += x->l->size;
		if (x->r) x->size += x->r->size;
	}
	void rotate(Node* x) {
		Node* p = x->p;
		Node* b = 0;
		if (!p) return; // if x is root, then return
		propagate(p);
		propagate(x);
		if (x == p->l) { // if x is left child
			p->l = b = x->r; // left of p is right of x
			x->r = p; // p becomes right child of x
		}
		else { // else if x is right child
			p->r = b = x->l; // right of p is left of x
			x->l = p; // p becomes left child of x
		}

		// set parent
		x->p = p->p;
		p->p = x;
		if (b) b->p = p;
		(x->p ? p == x->p->l ? x->p->l : x->p->r : root) = x;
		update(p); // p becomes child of x, so update first
		update(x); // update size of x
	}

	void splay(Node* x, Node* g = 0) {
		while (x->p != g) {
			Node* p = x->p;
			if (p->p == g) {
				rotate(x);
				break;
			}
			Node* pp = p->p;
			if ((p->l == x) == (pp->l == p)) {
				rotate(p); rotate(x);
			}
			else {
				rotate(x); rotate(x);
			}
		}
		if (!g) root = x;
	}
	void get(int i) {
		Node* x = root;
		propagate(x);
		while (1) {
			while (x->l && x->l->size > i) x = x->l, propagate(x);
			if (x->l) i -= x->l->size;
			if (!i--) break;
			x = x->r;
			propagate(x);
		}
		splay(x);
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
		root = new Node(-INF); // left dummy
		Node* cur = root;
		for (int i = 1, k; i <= n; ++i) {
			std::cin >> k;
			ptr[i] = cur->r = new Node(k);
			cur->r->p = cur;
			cur = cur->r;
		}
		cur->r = new Node(INF); // right dummy
		cur->r->p = cur;
		root->dummy = cur->r->dummy = 1;
		for (int i = n; i >= 1; --i) update(ptr[i]);
		splay(ptr[n / 2 + 1]);
	}

	void flip(int s, int e) {
		Node* x = gather(s, e);
		x->flip ^= 1;
	}

	void robotic_sort() {
		std::stable_sort(ptr + 1, ptr + N + 1, comp);
		for (int i = 1; i <= N; ++i) {
			splay(ptr[i]);
			int pi = root->l->size;
			std::cout << pi << ' ';
			flip(i, pi);
		}
		std::cout << '\n';
	}
} sp;


int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> N;

	while (N) {
		sp.init(N);
		sp.robotic_sort();
		std::cin >> N;
	}
}