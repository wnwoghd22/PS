#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int LEN = 100'001;

int A[LEN];

class SplayTree {
	struct Node {
		Node* l;
		Node* r;
		Node* p;
		int k, size, count, total;
		Node(int k) : l(0), r(0), p(0), k(k), size(1), count(1), total(1) {}
		~Node() { if (l) delete l; if (r) delete r; }
		void update() {
			size = 1;
			total = count;
			if (l) {
				size += l->size;
				total += l->total;
			}
			if (r) {
				size += r->size;
				total += r->total;
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
	void clear() { if (root) delete root; root = 0; }
	~SplayTree() { clear(); }
	void insert(int k) {
		if (!root) {
			root = new Node(k);
			return;
		}
		Node* p = root;
		Node** pp;
		while (1) {
			if (p->k == k) {
				p->count++;
				splay(p);
				return;
			}
			if (p->k > k) {
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
		Node* x = new Node(k);
		*pp = x;
		x->p = p;
		splay(x);
	}
	bool find(int k) {
		if (!root) return false;
		Node* p = root;
		while (1) {
			if (p->k == k) break;
			if (p->k > k) {
				if (!p->l) break;
				p = p->l;
			}
			else {
				if (!p->r) break;
				p = p->r;
			}
		}
		splay(p);
		return p->k == k;
	}
	void pop(int k) {
		if (!find(k)) return;
		// std::cout << "pop: " << k << ' ' << root->k << '\n';
		if (--root->count) return;
		Node* p = root;
		Node* l = p->l;
		Node* r = p->r;
		if (l && r) {
			root = l; l->p = 0;
			while (l->r) l = l->r;
			l->r = r; r->p = l;
		}
		else if (l) root = l, l->p = 0;
		else if (r) root = r, r->p = 0;
		else root = 0;
		p->l = p->r = 0;
		delete p;
	}
	int upper_count(int k) {
		find(k);
		if (!root) return 0;
		// std::cout << "upper: " << k << ' ' << root->k << '\n';
		if (root->k <= k) return root->r ? root->r->total : 0;
		if (root->k > k) return root->total - (root->l ? root->l->total : 0);
	}
} merge_tree[LEN * 4];

int N, M;
void init(int s = 1, int e = N, int i = 1) {
	for (int j = s; j <= e; ++j) merge_tree[i].insert(A[j]);
	if (s == e) return;
	int m = s + e >> 1;
	init(s, m, i << 1), init(m + 1, e, i << 1 | 1);
}

void update(int j, int k, int s = 1, int e = N, int i = 1) {
	if (j < s || e < j) return;
	// std::cout << "update: " << j << ' ' << s << ' ' << e << '\n';
	merge_tree[i].pop(A[j]);
	merge_tree[i].insert(k);
	if (s == e) {
		A[j] = k;
		return;
	}
	int m = s + e >> 1;
	update(j, k, s, m, i << 1);
	update(j, k, m + 1, e, i << 1 | 1);
}

int query(int l, int r, int k, int s = 1, int e = N, int i = 1) {
	if (r < s || e < l) return 0;
	// std::cout << "query: " << l << ' ' << r << ' ' << s << ' ' << e << '\n';
	if (l <= s && e <= r) return merge_tree[i].upper_count(k);
	int m = s + e >> 1;
	return query(l, r, k, s, m, i << 1) + query(l, r, k, m + 1, e, i << 1 | 1);
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	init();

	std::cin >> M;
	for (int m = 0, q, i, j, k; m < M; ++m) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> i >> j >> k;
			std::cout << query(i, j, k) << '\n';
		}
		if (q == 2) {
			std::cin >> i >> k;
			update(i, k);
		}
	}
}