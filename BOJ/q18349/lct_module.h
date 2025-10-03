#ifndef __BST_MODULE_H__
#define __BSD_MODULE_H__

typedef long long ll;

const int LCT_SZ = 90'001;

struct Node {
	Node* l, * r, * p;
	int s; // size
	bool f; // flip
	int i;
	ll v, max;
	void update();
	bool is_root();
	bool is_left();
	void rotate();
	void push();
};

struct LinkCutTree {
	Node t[LCT_SZ];

	void splay(Node* x);
	void access(Node* x);
	void link(Node* x, Node* p);
	void cut(Node* x);
	Node* get_lca(Node* x, Node* y);
	ll query(Node* x, Node* y);

	// insert a edge between u and v, make vertex u as child of v
	void link(int u, int v);
	ll query(int u, int v);
	void change_parent(int u, int p, ll w);
};

#endif