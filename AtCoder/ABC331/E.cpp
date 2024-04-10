#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const int LEN = 1e5 + 1;
class SplayTree {
public:
	struct Node {
		Node* l;
		Node* r;
		Node* p;
		ll val;
		int size;
		int cnt;
		Node(ll val) : l(0), r(0), p(0), val(val), size(1), cnt(1) {}
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
	ll get_max() {
		if (!root) return -1;
		Node* p = root;
		while (p->r) p = p->r;
		splay(p);
		return p->val;
	}
} sp;

int N, M, L;
ll A[LEN], B[LEN];
std::vector<ll> pairs[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	ll max = 0;
	std::cin >> N >> M >> L;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	for (int i = 1; i <= M; ++i) {
		std::cin >> B[i];
		sp.insert(B[i]);
	}
	for (int i = 1, c, d; i <= L; ++i) {
		std::cin >> c >> d;
		pairs[c].push_back(d);
	}
	for (int c = 1; c <= N; ++c) {
		for (const int& d : pairs[c]) sp.pop(B[d]);
		max = std::max(max, sp.get_max() + A[c]);
		for (const int& d : pairs[c]) sp.insert(B[d]);
	}
	std::cout << max;
}