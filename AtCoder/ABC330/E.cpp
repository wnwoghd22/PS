#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 2e5 + 1;
class SplayTree {
public:
	struct Node {
		Node* l;
		Node* r;
		Node* p;
		ll val;
		ll max, min;
		int size;
		int cnt;
		Node(ll val) : l(0), r(0), p(0), val(val), max(val), min(val), size(1), cnt(1) {}
		~Node() { if (l) delete l; if (r) delete r; }
		void update() {
			size = 1;
			min = max = val;
			if (l) {
				size += l->size;
				min = l->min;
			}
			if (r) {
				size += r->size;
				max = r->max;
			}
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
	~SplayTree() { if (root) delete root; }
	int size() { return root ? root->size : 0; }
	void insert(ll val) {
		if (!root) {
			root = new Node(val);
			return;
		}
		Node* p = root;
		Node** pp;
		while (1) {
			if (p->val == val) {
				p->cnt++;
				return;
			}
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
		Node* x = new Node(val);
		x->p = p;
		*pp = x;
		splay(x);
	}
	bool find(ll val) {
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
	void pop(ll val) {
		if (!find(val)) return;
		Node* p = root;
		if (--p->cnt) return;

		if (p->l && p->r) {
			root = p->l; root->p = 0;
			Node* l = root;
			while (l->r) l = l->r;
			l->r = p->r;
			p->r->p = l;
			splay(p->r);
		}
		else if (p->l) root = p->l, root->p = 0;
		else if (p->r) root = p->r, root->p = 0;
		else root = 0;
		p->l = p->r = 0;
		delete p;
	}
	ll get(int i) {
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
} sp;

ll N, Q, A[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> Q;

	sp.insert(-1); sp.insert(1e9 + 7); sp.insert(1e9 + 8);
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		sp.insert(A[i]);
	}
	for (int q = 0, i, x; q < Q; ++q) {
		std::cin >> i >> x;
		// std::cout << "pop ";
		sp.pop(A[i]);
		A[i] = x;
		// std::cout << "push ";
		sp.insert(A[i]);
		int mex = 0;
		int l = 1, r = sp.size() - 1, m, result = 1;
		while (l <= r) {
			m = l + r >> 1;
			// std::cout << "get " << m << '\n';
			sp.get(m);
			SplayTree::Node* range = sp.root->l;
			if (range->size == range->max - range->min + 1) { /// contiguous
				result = std::max(result, m);
				l = m + 1;
			}
			else r = m - 1;
		}
		sp.get(result);
		std::cout << sp.root->l->max + 1 << '\n';
	}
}