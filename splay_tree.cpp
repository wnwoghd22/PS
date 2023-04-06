typedef long long ll;

class SplayTree {
private:
	struct Node {
		Node* l; // left
		Node* r; // right
		Node* p; // parent
		int size;
		ll val;
		Node(ll val) : l(0), r(0), p(0), size(1), val(val) {}
		~Node() { if (l) delete l; if (r) delete r; }
		void update() {
			size = 1;
			if (l) size += l->size;
			if (r) size += r->size;
		}
	} *root;
	void rotate(Node* x) {
		Node* p = x->p;
		if (!p) return; // x is root
		Node* b = 0;
		if (x == p->l) { // if x is left of p
			p->l = b = x->r; // right of x becomes left of p
			x->r = p; // p becomes right of p
		}
		else { // else if x is right of p
			p->r = b = x->l; // left of x becomes right of p
			x->l = p; // p becomes left of p
		}
		// set parent
		x->p = p->p;
		p->p = x;
		if (b) b->p = p;
		(x->p ? p == x->p->l ? x->p->l : x->p->r : root) = x;
		p->update();
		x->update();
	}
	void splay(Node* x) {
		while (x->p) { // while x is not root
			Node* p = x->p; // parent
			Node* g = p->p; // grand parent
			if (g) {
				if ((x == p->l) == (p == g->l)) rotate(p); // zig-zig
				else rotate(x); // zig-zag
			}
			rotate(x); // zig
		}
	}
public:
	SplayTree() : root(0) {}
	~SplayTree() { if (root) delete root; }
	int size() { return root ? root->size : 0; }
	void insert(ll val) {
		Node* p = root;
		Node** pp; // insertion position
		if (!p) { // empty root
			root = new Node(val);
			return;
		}
		while (1) {
			if (val == p->val) return; // already exists
			if (val < p->val) { // left
				if (!p->l) {
					pp = &p->l;
					break;
				}
				p = p->l;
			}
			else { // right
				if (!p->r) {
					pp = &p->r;
					break;
				}
				p = p->r;
			}
		}
		Node* x = new Node(val);
		*pp = x;
		x->p = p;
		splay(x);
	}
	bool find(ll val) {
		Node* p = root;
		if (!p) return false; // empty
		while (1) {
			if (val == p->val) break; // exists
			if (val < p->val) { // left
				if (!p->l) break;
				p = p->l;
			}
			else { // right
				if (!p->r) break;
				p = p->r;
			}
		}
		splay(p);
		return val == p->val;
	}
	void pop(ll val) {
		if (!find(val)) return;
		Node* p = root;
		if (p->l && p->r) {
			root = p->l; root->p = 0;
			Node* x = root;
			while (x->r) x = x->r;
			x->r = p->r; p->r->p = x;
		}
		else if (p->l) { root = p->l; root->p = 0; }
		else if (p->r) { root = p->r; root->p = 0; }
		else root = 0;

		delete p;
	}

	ll get(int i) { // 1-base
		Node* p = root;
		while (1) {
			while (p->l && p->l->size > i) p = p->l;
			if (p->l) i -= p->l->size;
			if (!i--) break;
			p = p->r;
		}
		splay(p);
		return p->val;
	}
};