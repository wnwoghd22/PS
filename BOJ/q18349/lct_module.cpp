#include <iostream>
#include <cstring>
#include <queue>

#include "lct_module.h"

const ll INF = 1e17;

void Node::update() {
		s = 1;
		max = v;
		if (l) {
			s += l->s;
			if (l->max > max) 
				max = l->max;
		}
		if (r) {
			s += r->s;
			if (r->max > max) 
				max = r->max;
		}
	}
bool Node::is_root() { return !p || (p->l != this && p->r != this); }
bool Node::is_left() { return p->l == this; }
void Node::rotate() {
	if (is_left()) r && (r->p = p), p->l = r, r = p;
	else l && (l->p = p), p->r = l, l = p;

	if (!p->is_root()) (p->is_left() ? p->p->l : p->p->r) = this;
	Node* y = p; p = y->p; y->p = this;
	y->update(); update();
}
void Node::push() {
	if (f) {
		if (l) l->f ^= 1;
		if (r) r->f ^= 1;
		std::swap(l, r);
		f = 0;
	}
}

void LinkCutTree::splay(Node* x) {
	for (Node* p; !x->is_root(); x->rotate()) {
		p = x->p;
		if (!p->is_root()) p->p->push(); p->push(); x->push();
		if (p->is_root()) continue;	// zig
		if (x->is_left() == p->is_left()) p->rotate();	// zig-zig
		else x->rotate();	// zig-zag
	}
	x->push();
}
void LinkCutTree::access(Node* x) {
	splay(x); x->r = 0; x->update();
	for (; x->p; splay(x))
		splay(x->p), x->p->r = x;
}
void LinkCutTree::link(Node* x, Node* p) {
	access(x);
	access(p);
	p->p = x; x->l = p;
	x->update();
}
void LinkCutTree::cut(Node* x) {
	access(x);
	if (!x->l) return;
	x->l = x->l->p = 0;
	x->update();
}
Node* LinkCutTree::get_lca(Node* x, Node* y) {
	access(x); access(y); splay(x);
	return x->p ? x->p : x;
}
ll  LinkCutTree::query(Node* x, Node* y) {
	Node* l = get_lca(x, y);
	ll result = -INF;

	access(x); splay(l);
	if (l->r && l->r->max > result)
		result = l->r->max;

	access(y); splay(l);
	if (l->r && l->r->max > result)
		result = l->r->max;

	return result;
}
void LinkCutTree::link(int u, int v) { link(&t[u], &t[v]); }
ll LinkCutTree::query(int u, int v) { return u == v ? 0 : query(&t[u], &t[v]); }
void LinkCutTree::change_parent(int u, int p, ll w) {
	cut(&t[u]);
	link(u, p);
	t[u].v = w;
	access(&t[u]);
}
