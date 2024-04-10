#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long int ll;
const int INF = 1e9;

class SplayTree {
	struct Node {
		Node* l; // left
		Node* r; // right
		Node* p; // parent
		int key;
		int size; // size of subtree
		ll val, sum;
	} *root;
	void update(Node* x) {
		x->size = 1;
		x->sum = x->val;
		if (x->l) x->size += x->l->size, x->sum += x->l->sum;
		if (x->r) x->size += x->r->size, x->sum += x->r->sum;
	}
	void rotate(Node* x) {
		Node* p = x->p;
		Node* b = 0;
		if (!p) return; // if x is root, then return
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
		Node* y;
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
public:
	SplayTree() : root(0) {}
	void insert(int key, ll val) {
		Node* p = root;
		Node** pp;
		if (!p) { // if tree is empty
			Node* x = new Node;
			root = x;
			x->l = x->r = x->p = 0;
			x->key = key;
			x->sum = x->val = val;
			return;
		}
		while (1) {
			if (key == p->key) return;
			if (key < p->key) { // smaller -> left child
				if (!p->l) {
					pp = &p->l;
					break;
				}
				p = p->l;
			}
			else { // bigger -> right child
				if (!p->r) {
					pp = &p->r;
					break;
				}
				p = p->r;
			}
		}
		Node* x = new Node;
		*pp = x;
		x->l = x->r = 0;
		x->p = p, x->key = key; x->sum = x->val = val;
		splay(x);
	}
	bool find(int key) {
		Node* p = root;
		if (!p) return false;
		while (p) {
			if (key == p->key) break; // found key
			if (key < p->key) { // smaller -> left child
				if (!p->l) break; // fail
				p = p->l;
			}
			else { // bigger -> right child
				if (!p->r) break; // fail
				p = p->r;
			}
		}
		splay(p);
		return key == p->key;
	}

	void remove(int key) {
		if (!find(key)) return; // move target node to root
		Node* p = root;
		if (p->l && p->r) { // two children
			root = p->l; root->p = 0; // set left new root

			Node* x = root;
			while (x->r) x = x->r; // find biggest in left
			x->r = p->r; p->r->p = x; // attach right to left
			delete p;
			return;
		}
		else if (p->l) { // has left only
			root = p->l; root->p = 0;
			delete p;
			return;
		}
		else if (p->r) { // has right only
			root = p->r; root->p = 0;
			delete p;
			return;
		}
		delete p; root = 0;
	}

	int get(int i) {
		Node* x = root;
		while (1) {
			while (x->l && x->l->size > i) x = x->l;
			if (x->l) i -= x->l->size;
			if (!i--) break;
			x = x->r;
		}
		splay(x);

		return x->key;
	}

	ll get_sum(int s, int e) {
		get(e + 1);
		Node* temp = root;
		get(s - 1);
		splay(temp, root);
		return root->r->l->sum;
	}

	void update_val(int i, ll d) {
		find(i);
		root->val = d;
	}
};

int N, M, K, Q;
ll A, B, C;

int main() {
	freopen("input.txt", "r", stdin);

	SplayTree sp;
	std::cin >> N >> M >> K;
	sp.insert(-INF, 0); // put dummy
	for (int i = 1; i <= N; ++i) {
		std::cin >> A;
		sp.insert(i, A);
	}
	sp.insert(INF, 0); // put dummy

	Q = M + K;
	while (Q--) {
		std::cin >> A >> B >> C;
		if (A == 1) sp.update_val(B, C);
		if (A == 2) std::cout << sp.get_sum(B, C) << '\n';
	}
}