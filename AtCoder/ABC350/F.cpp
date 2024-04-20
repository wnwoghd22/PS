#include <iostream>
#include <cstring>
#include <vector>

const int LEN = 500'001;

class SplayTree {
public:
	struct Node {
		Node* l; // left
		Node* r; // right
		Node* p; // parent
		int val;
		int size;
		int flip_cnt;
		int lazy_cnt;
		Node(int val) : l(0), r(0), p(0), val(val), size(1), flip_cnt(0), lazy_cnt(0) {}
		~Node() { if (l) delete l; if (r) delete r; }
		void propagate() {
			if (lazy_cnt) {
				// std::cout << "propagate: " << val << ' ' << lazy_cnt << '\n';
				if (lazy_cnt & 1) std::swap(l, r);
				if (l) l->lazy_cnt += lazy_cnt;
				if (r) r->lazy_cnt += lazy_cnt;
				flip_cnt += lazy_cnt;	
			}
			lazy_cnt = 0;
		}
		void update() {
			size = 1;
			if (l) size += l->size;
			if (r) size += r->size;
		}
	} *root;
	void rotate(Node* x) {
		Node* p = x->p;
		Node* b = 0;
		if (!p) return; // root
		p->propagate();
		x->propagate();
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
				if ((x == p->l) && (p == g->l)) rotate(p);
				else rotate(x);
			}
			rotate(x);
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
	SplayTree() : root(0) { }
	~SplayTree() { if (root) delete root; }
	void init(int n) {
		if (root) delete root;
		root = new Node(-1);
		Node* cur = root;
		for (int i = 1; i <= n; ++i) {
			cur->r = new Node(i);
			cur->r->p = cur;
			cur = cur->r;
		}
		Node* tail = new Node(-1);
		cur->r = tail;
		cur->r->p = cur;
		splay(tail);
	}
	Node* get(int i) {
		Node* x = root;
		if (!x) return 0;
		x->propagate();
		while (1) {
			while (x->l && x->l->size > i) x = x->l, x->propagate();
			if (x->l) i -= x->l->size;
			if (!i--) break;
			x = x->r;
			x->propagate();
		}
		splay(x);
		return x;
	}
	void flip(int s, int e) {
		Node* x = gather(s, e);
		x->lazy_cnt++;
		// std::cout << x->val << '\n';
		// std::cout << x->lazy_cnt << '\n';
	}
} st;

int N, M = 1;
char S[LEN];
char X[LEN];
std::vector<int> stack;

int main() {
	std::cout.tie(0);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> S;
	for (int i = 0; S[i]; ++i) if (S[i] != '(' && S[i] != ')') N++;
	st.init(N);
	for (int i = 0; S[i]; ++i) {
		if (S[i] == '(') {
			stack.push_back(M);
			continue;
		}
		if (S[i] == ')') {
			int l = stack.back();
			stack.pop_back();
			int r = M - 1;
			// std::cout << "flip: " << l << ' ' << r << '\n';
			if (l <= r) st.flip(l, r);
			continue;
		}
		X[M++] = S[i];
	}
	// std::cout << (X + 1) << '\n';
	// for (int i = 1; i < M; ++i) st.get(i);

	int term = 'a' - 'A';
	for (int i = 1; i < M; ++i) {
		SplayTree::Node* now = st.get(i);
		int flipped = now->flip_cnt;
		int idx = now->val;
		char c = X[idx];
		if (flipped & 1) {
			if (c <= 'Z') c += term;
			else if (c >= 'a') c -= term;
		}
		std::cout << c;
	}
}