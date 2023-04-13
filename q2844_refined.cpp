#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long ll;

class SplayTree {
	struct Node {
		Node* l;
		Node* r;
		Node* p;
		int size;
		ll val, sum;
		ll x, a0, d; // eff, a0, diff
		Node() : l(0), r(0), p(0), size(1), val(0), sum(0), x(1), a0(0), d(0) {}
		~Node() { if (l) delete l; if (r) delete r; }
		void push(ll x, ll a0, ll d) {
			this->x *= x; this->a0 *= x; this->d *= x;
			this->a0 += a0; this->d += d;
		}
		void propagate() {
			if (!x || a0 || d) {
				int pivot = (l ? l->size : 0) + 1;
				val = val * x + a0 + d * pivot;
				sum = x * sum + a0 * size + d * size * (size + 1) / 2;
				if (l) l->push(x, a0, d);
				if (r) r->push(x, a0 + d * pivot, d);
				x = 1; a0 = 0; d = 0;
			}
		}
		void update() {
			size = 1;
			sum = val;
			if (l) {
				l->propagate();
				size += l->size;
				sum += l->sum;
			}
			if (r) {
				r->propagate();
				size += r->size;
				sum += r->sum;
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
		p->propagate();
		while (1) {
			while (p->l && p->l->size > i) p = p->l, p->propagate();
			if (p->l) i -= p->l->size;
			if (!i--) break;
			p = p->r;
			p->propagate();
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
			next->val = next->sum = x;
			cur->r = next; next->p = cur;
			cur = next;
		}
		Node* tail = new Node; // dummy
		cur->r = tail; tail->p = cur;
		splay(tail);
	}
	void insert(int c, ll x) {
		get(c);
		Node* r = root;
		get(c - 1);
		Node* l = root;
		splay(r, l);
		Node* m = new Node;
		m->sum = m->val = x;
		m->r = r; r->p = m;
		m->p = l; l->r = m;
		m->update();
		l->update();
	}
	ll get_sum(int s, int e) { return gather(s, e)->sum; }
	void push(int s, int e, ll x, ll a0, ll d) { gather(s, e)->push(x, a0, d); }

	ll debug(int i) {
		get(i);
		return root->val;
	}
} sp;
int N, Q;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	std::cin >> N >> Q;
	sp.init(N);

	for (int i = 0, q, a, b, c, x; i < Q; ++i) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> a >> b >> x;
			sp.push(a, b, 0, x, 0);
		}
		if (q == 2) {
			std::cin >> a >> b >> x;
			sp.push(a, b, 1, 0, x);
		}
		if (q == 3) {
			std::cin >> c >> x;
			sp.insert(c, x);
		}
		if (q == 4) {
			std::cin >> a >> b;
			std::cout << sp.get_sum(a, b) << '\n';
		}
	}
}