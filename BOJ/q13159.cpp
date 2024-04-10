#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long int ll;
const int INF = 1e9;
const int LEN = 300'002;

class SplayTree {
	struct Node {
		Node* l; // left
		Node* r; // right
		Node* p; // parent
		int size; // size of subtree
		ll val, sum, min, max;
		bool flip;
		bool dummy;
		Node(ll val) : l(0), r(0), p(0), size(1), val(val), sum(val), min(val), max(val), flip(0), dummy(0) {}
		~Node() { if (l) delete l; if (r) delete r; }
	} *root, * ptr[LEN];
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
		x->sum = x->min = x->max = x->val;
		if (x->l) {
			x->size += x->l->size;
			x->sum += x->l->sum;
			x->min = std::min(x->min, x->l->min);
			x->max = std::max(x->max, x->l->max);
		}
		if (x->r) {
			x->size += x->r->size;
			x->sum += x->r->sum;
			x->min = std::min(x->min, x->r->min);
			x->max = std::max(x->max, x->r->max);
		}
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

	void splay(Node* x) {
		while (x->p) { // while x is not root
			Node* p = x->p;
			Node* g = p->p;
			if (g) {
				if ((x == p->l) == (p == g->l)) rotate(p); // Zig-Zig
				else rotate(x); // Zig-Zag
			}
			rotate(x); // Zig
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
		for (int i = 1; i <= n; ++i) {
			ptr[i] = cur->r = new Node(i);
			cur->r->p = cur;
			cur = cur->r;
		}
		cur->r = new Node(INF); // right dummy
		cur->r->p = cur;
		root->dummy = cur->r->dummy = 1;
		splay(ptr[n / 2]);
	}

	void flip(int s, int e) {
		Node* x = gather(s, e);
		x->flip ^= 1;
	}

	void flip_query(int s, int e) {
		Node* x = gather(s, e);
		x->flip ^= 1;
		std::cout << x->min << ' ' << x->max << ' ' << x->sum << '\n';
	}

	void shift(int s, int e, int k) {
		Node* x = gather(s, e);
		std::cout << x->min << ' ' << x->max << ' ' << x->sum << '\n';
		if (k >= 0) {
			k %= (e - s + 1);
			if (!k) return;
			flip(s, e); flip(s, s + k - 1); flip(s + k, e);
		}
		else {
			k *= -1;
			k %= (e - s + 1);
			if (!k) return;
			flip(s, e); flip(s, e - k); flip(e - k + 1, e);
		}
	}
	void get_index(int x) {
		splay(ptr[x]);
		std::cout << root->l->size << '\n';
	}
	void find(int i) {
		get(i);
		std::cout << root->val << '\n';
	}
	void print(Node* x) {
		propagate(x);
		if (x->l) print(x->l);
		if (!x->dummy) std::cout << x->val << ' ';
		if (x->r) print(x->r);
	}
	void print() { print(root); }
} sp;

int N, Q, q;
ll l, r, i, x;

int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> N >> Q;
	sp.init(N);

	while (Q--) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> l >> r;
			sp.flip_query(l, r);
		}
		if (q == 2) {
			std::cin >> l >> r >> x;
			sp.shift(l, r, x);
		}
		if (q == 3) {
			std::cin >> i;
			sp.find(i);
		}
		if (q == 4) {
			std::cin >> x;
			sp.get_index(x);
		}
	}
	sp.print();
}