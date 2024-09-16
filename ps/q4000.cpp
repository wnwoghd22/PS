#include <iostream>
#include <algorithm>
#include <map>

typedef long long ll;
const int LEN = 200'001;

struct Pos {
	int x, y;
	int i, d;
	bool operator<(const Pos& r) const { return x == r.x ? y == r.y ? d < r.d : y < r.y : x < r.x; }
	bool operator==(const Pos& r) const { return x == r.x && y == r.y; }
} cur, pos[LEN << 1];

int cross(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) {
	ll result = (ll)(p2.x - p1.x) * (p4.y - p3.y) - (ll)(p2.y - p1.y) * (p4.x - p3.x);
	if (!result) return 0;
	if (result > 0) return 1;
	return -1;
}
int dot(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) {
	ll result = (ll)(p2.x - p1.x) * (p4.x - p3.x) + (ll)(p2.y - p1.y) * (p4.y - p3.y);
	if (!result) return 0;
	if (result > 0) return 1;
	return -1;
}

struct Segment {
	Pos l, r;
	bool operator<(const Segment& rhs) const {
		if (l == rhs.l) return cross(rhs.l, rhs.r, rhs.r, r) < 0;
		if (rhs.l < l) return cross(rhs.l, rhs.r, rhs.r, l) < 0;
		return cross(rhs.l, rhs.r, rhs.r, r) < 0;
	}
} segments[LEN];

bool intersect(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) {
	bool f11 = cross(p1, p2, p2, p3) * cross(p2, p1, p1, p4) > 0;
	bool f12 = cross(p3, p4, p4, p1) * cross(p4, p3, p3, p2) > 0;
	bool line = !cross(p1, p3, p3, p2) && dot(p1, p3, p3, p2) > 0 ||
		!cross(p1, p4, p4, p2) && dot(p1, p4, p4, p2) > 0 ||
		!cross(p3, p1, p1, p4) && dot(p3, p1, p1, p4) > 0 ||
		!cross(p3, p2, p2, p4) && dot(p3, p2, p2, p4) > 0;
	return f11 && f12 || line;
}
bool intersects(int a, int b) { return intersect(segments[a].l, segments[a].r, segments[b].l, segments[b].r); }

class SplayTree {
	struct Node {
		int i;
		Node* l;
		Node* r;
		Node* p;
		Node(int i) : i(i), l(0), r(0), p(0) {}
		~Node() { if (l) delete l; if (r) delete r; }
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
	~SplayTree() { if (root) delete root; root = 0; }
	void clear() { if (root) delete root; root = 0; }
	bool insert(int i) {
		if (!root) {
			root = new Node(i);
			return false;
		}
		Node* p = root;
		Node** pp;
		while (1) {
			if (p->i == i) return false;
			if (segments[i] < segments[p->i]) {
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
		Node* x = new Node(i);
		x->p = p;
		*pp = x;
		splay(x);

		if (x->l) {
			Node* l = x->l;
			while (l->r) l = l->r;
			if (intersects(l->i, i)) return true;
			splay(l);
		}

		splay(x);
		if (x->r) {
			Node* r = x->r;
			while (r->l) r = r->l;
			if (intersects(r->i, i)) return true;
			splay(r);
		}

		splay(x);
		return false;
	}
	bool find(int i) {
		if (!root) return 0;
		Node* p = root;
		while (1) {
			if (p->i == i) break;
			if (segments[i] < segments[p->i]) {
				if (!p->l) break;
				p = p->l;
			}
			else {
				if (!p->r) break;
				p = p->r;
			}
		}
		splay(p);
		return p->i == i;
	}
	bool pop(int i) {
		if (!find(i)) return false;
		Node* p = root;

		if (p->l && p->r) {
			Node* l = p->l;
			Node* r = p->r;
			root = l; root->p = 0;
			while (l->r) l = l->r;
			l->r = r;
			r->p = l;
			while (r->l) r = r->l;
			if (intersects(l->i, r->i)) return true;
			splay(r);
		}
		else if (p->l) root = p->l, root->p = 0;
		else if (p->r) root = p->r, root->p = 0;
		else root = 0;
		p->l = p->r = 0;
		delete p;
		return false;
	}
} s;

int N[3];
bool poly[3];

Pos A[3][LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	for (int k = 0; k < 3; ++k) {
		// std::cout << "test " << k << '\n';
		s.clear();
		std::cin >> N[k];
		poly[k] = 1;
		std::map<ll, int> cnt;
		for (int i = 0; i < N[k]; ++i) {
			std::cin >> A[k][i].x >> A[k][i].y;
			ll key = A[k][i].x * 1'000'000ll + A[k][i].y;
			if (cnt.find(key) != cnt.end()) {
				poly[k] = 0;
				break;
			}
			cnt[key] = 1;
		}
		if (!poly[k]) break;

		for (int i = 0, j; i < N[k]; ++i) {
			j = (i + 1) % N[k];
			segments[i] = { A[k][i], A[k][j] };
			if (segments[i].r < segments[i].l) std::swap(segments[i].l, segments[i].r);
			segments[i].l.i = i; segments[i].l.d = 1;
			segments[i].r.i = i; segments[i].r.d = -1;
			pos[i << 1] = segments[i].l;
			pos[i << 1 | 1] = segments[i].r;
		}
		std::sort(pos, pos + N[k] * 2);
		for (int i = 0; i < N[k] * 2; ++i) {
			if (~pos[i].d) {
				if (s.insert(pos[i].i)) {
					poly[k] = 0;
					break;
				}
			}
			else {
				if (s.pop(pos[i].i)) {
					poly[k] = 0;
					break;
				}
			}
		}
	}
	if (!poly[0]) {
		std::cout << "Aastria is not a polygon";
		return 0;
	}
	if (!poly[1]) {
		std::cout << "Abstria is not a polygon";
		return 0;
	}
	if (!poly[2]) {
		std::cout << "Aabstria is not a polygon";
		return 0;
	}

	std::cout << "Not implemented";
}