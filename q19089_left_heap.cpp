#include <iostream>

typedef long long ll;

// leftist heap
class LeftistHeap {
private:
	struct Node {
		ll e;
		Node* l;
		Node* r;
		int dist; // null path length
		Node(const ll& e, Node* l = 0, Node* r = 0, const int& d = 0) : e(e), l(l), r(r), dist(d) {}
		void swap_children() { Node* t = l; l = r; r = t; }
	} *root;
	Node* merge(Node* h1, Node* h2);
	Node* merge_in(Node* h1, Node* h2);
	void reclaim_memory(Node* n);
	Node* clone(Node* n);
public:
	LeftistHeap();
	LeftistHeap(LeftistHeap& r);
	~LeftistHeap();
	bool empty();
	bool full();
	void insert(ll& x);
	ll& find_min();
	void delete_min();
	void delete_min(ll& min);
	void clear();
	void merge(LeftistHeap& r);
	LeftistHeap& operator=(LeftistHeap& r);
};

LeftistHeap::LeftistHeap() : root(0) {}
LeftistHeap::LeftistHeap(LeftistHeap& r) : root(0) { *this = r; }
LeftistHeap::~LeftistHeap() { clear(); }
void LeftistHeap::merge(LeftistHeap& r) {
	if (this == &r) return;
	root = merge(root, r.root);
	r.root = 0;
}
LeftistHeap::Node* LeftistHeap::merge(Node* h1, Node* h2) {
	if (h1 == 0) return h2;
	if (h2 == 0) return h1;
	return h1->e < h2->e ? merge_in(h1, h2) : merge_in(h2, h1);
}
LeftistHeap::Node* LeftistHeap::merge_in(Node* h1, Node* h2) {
	if (h1->l == 0) h1->l = h2;
	else {
		h1->r = merge(h1->r, h2);
		if (h1->l->dist < h1->r->dist)
			h1->swap_children();
		h1->dist = h1->r->dist + 1;
	}
	return h1;
}
void LeftistHeap::insert(ll& x) {
	root = merge(new LeftistHeap::Node(x), root);
}
ll& LeftistHeap::find_min() { return root->e; }
void LeftistHeap::delete_min() {
	LeftistHeap::Node* old = root;
	root = merge(root->l, root->r);
	delete old;
}
void LeftistHeap::delete_min(ll& min) {
	if (empty()) return;
	min = find_min();
	delete_min();
}
bool LeftistHeap::empty() { return root == 0; }
bool LeftistHeap::full() { return false; }
void LeftistHeap::clear() {
	reclaim_memory(root);
	root = 0;
}
LeftistHeap& LeftistHeap::operator=(LeftistHeap& r) {
	if (this != &r) {
		clear();
		root = clone(r.root);
	}
	return *this;
}
void LeftistHeap::reclaim_memory(LeftistHeap::Node* n) {
	if (n) {
		reclaim_memory(n->l);
		reclaim_memory(n->r);
		delete n;
	}
}
LeftistHeap::Node* LeftistHeap::clone(LeftistHeap::Node* n) {
	if (!n) return 0;
	else return new LeftistHeap::Node(n->e, clone(n->l), clone(n->r), n->dist);
}

using namespace std;

int main() {
	LeftistHeap h;
	LeftistHeap h1;
	LeftistHeap h2;
	ll x;
	ll arr[] = { 1, 5, 7, 10, 15 };
	ll arr1[] = { 22, 75 };

	h.insert(arr[0]);
	h.insert(arr[1]);
	h.insert(arr[2]);
	h.insert(arr[3]);
	h.insert(arr[4]);
	h1.insert(arr1[0]);
	h1.insert(arr1[1]);

	h.delete_min(x);
	cout << x << endl;

	h1.delete_min(x);
	cout << x << endl;

	h.merge(h1);
	h2 = h;

	h2.delete_min(x);
	cout << x << endl;

	return 0;
}