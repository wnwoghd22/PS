typedef long long ll;
const int LEN = 200'001;

class LeftistHeap {
private:
	struct Node {
		ll e;
		Node* l;
		Node* r;
		int dist; // null path length
		Node(const ll& e, Node* l = 0, Node* r = 0, const int& d = 0) : e(e), l(l), r(r), dist(d) {}
		~Node() { if (l) delete l; if (r) delete r; }
		void swap_children() { Node* t = l; l = r; r = t; }
	} *root;
	Node* merge_in(Node* h1, Node* h2) {
		if (h1->l == 0) h1->l = h2;
		else {
			h1->r = merge(h1->r, h2);
			if (h1->l->dist < h1->r->dist)
				h1->swap_children();
			h1->dist = h1->r->dist + 1;
		}
		return h1;
	}
	Node* merge(Node* h1, Node* h2) {
		if (h1 == 0) return h2;
		if (h2 == 0) return h1;
		return h1->e < h2->e ? merge_in(h1, h2) : merge_in(h2, h1); // min heap
	}
	Node* clone(Node* n) {
		if (!n) return 0;
		else return new Node(n->e, clone(n->l), clone(n->r), n->dist);
	}
public:
	LeftistHeap() : root(0) {}
	LeftistHeap(LeftistHeap& r) : root(0) { *this = r; }
	~LeftistHeap() { clear(); }
	bool empty() { return root == 0; }
	void push(ll x) { root = merge(new Node(x), root); }
	ll top() { return root->e; }
	ll pop() {
		if (empty()) return -1;
		ll min = top();
		Node* old = root;
		root = merge(root->l, root->r);
		old->l = old->r = 0;
		delete old;
		return min;
	}
	void clear() { if (root) delete root; root = 0; }
	void merge(LeftistHeap& r) {
		if (this == &r) return;
		root = merge(root, r.root);
		r.root = 0;
	}
	LeftistHeap& operator=(LeftistHeap& r) {
		if (this != &r) {
			clear();
			root = clone(r.root);
		}
		return *this;
	}
} heaps[LEN];