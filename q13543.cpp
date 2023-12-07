#include <iostream>

typedef unsigned int ll;

ll C[11][11];

class SplayTree {
	struct Node {
		Node* l;
		Node* r;
		Node* p;
		int size;
		ll val, sum[11];
		Node() : l(0), r(0), p(0), size(1), val(0) {}
		~Node() { if (l) delete l; if (r) delete r; }
		void update() {
			static ll Y[11];
			size = 1;
			if (l) size += l->size;
			for (int i = Y[0] = 1; i <= 10; ++i)
				Y[i] = Y[i - 1] * size;
			if (r) size += r->size;
			for (int i = 0; i <= 10; ++i) {
				sum[i] = val * Y[i];
				if (l) sum[i] += l->sum[i];
				if (r) for (int j = 0; j <= i; ++j)
					sum[i] += C[i][j] * Y[i - j] * r->sum[j];
			}
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
	void splay(Node* x, Node* g = 0) {
		while (x->p != g) {
			Node* p = x->p;
			if (p->p == g) {
				rotate(x);
				break;
			}
			Node* pp = p->p;
			if ((x == p->l) == (p == pp->l)) rotate(p), rotate(x);
			else rotate(x), rotate(x);
		}
		if (!g) root = x;
	}
	void get(int i) {
		Node* p = root;
		if (!p) return;
		while (1) {
			while (p->l && p->l->size > i) p = p->l;
			if (p->l) i -= p->l->size;
			if (!i--) break;
			p = p->r;
		}
		splay(p);
	}
	Node* gather(int s, int e) {
		get(e + 1);
		Node* r = root;
		get(s - 1);
		Node* l = root;
		splay(r, l);
		l->r->l->update();
		return l->r->l;
	}
public:
	SplayTree() : root(0) {}
	~SplayTree() { if (root) delete root; }
	void init(int n) {
		if (root) delete root;
		root = new Node; // dummy
		Node* cur = root;
		ll x;
		for (int i = 0; i < n; ++i) {
			std::cin >> x;
			Node* next = new Node;
			next->val = x;
			cur->r = next; next->p = cur;
			cur = next;
		}
		Node* tail = new Node; // dummy
		cur->r = tail; tail->p = cur;
		splay(tail);
	}
	void insert(int p, ll x) {
		get(p);
		Node* r = root;
		Node* l = root->l;
		Node* m = new Node;
		m->val = x;
		m->l = l; l->p = m;
		m->p = r; r->l = m;
		m->update();
		r->update();
	}
	void update(int p, ll x) {
		get(p);
		root->val = x;
		root->update();
	}
	void pop(int i) {
		get(i);
		Node* p = root;

		if (p->l && p->r) {
			Node* l = p->l;
			Node* r = p->r;
			root = l; root->p = 0;
			while (l->r) l = l->r;
			l->r = r;
			r->p = l;
			splay(r);
		}
		else if (p->l) root = p->l, root->p = 0;
		else if (p->r) root = p->r, root->p = 0;
		else root = 0;
		p->l = p->r = 0;
		delete p;
	}
	ll get_sum(int l, int r, int k) { return gather(l, r)->sum[k]; }
} sp;
int N, Q;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	for (int i = C[0][0] = 1; i <= 10; ++i)
		for (int j = C[i][0] = 1; j <= i; ++j)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];

	std::cin >> N;
	sp.init(N);

	std::cin >> Q;
	for (int i = 0, q, p, v, l, r, k; i < Q; ++i) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> p >> v;
			sp.insert(p + 1, v);
		}
		if (q == 2) {
			std::cin >> p;
			sp.pop(p + 1);
		}
		if (q == 3) {
			std::cin >> p >> v;
			sp.update(p + 1, v);
		}
		if (q == 4) {
			std::cin >> l >> r >> k;
			std::cout << sp.get_sum(l + 1, r + 1, k) << '\n';
		}
	}
}