#include <iostream>
#include <cstring>

const int LEN = 30'001;

int N, Q;
int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

struct LinkCutTree {
	struct Node {
		int l, r, p;
		int s; // size
		bool f; // flip
		int v, sum;
	} t[LEN];
	void update(int x) {
		t[x].s = 1;
		t[x].sum = t[x].v;
		if (t[x].l) t[x].s += t[t[x].l].s, t[x].sum += t[t[x].l].sum;
		if (t[x].r) t[x].s += t[t[x].r].s, t[x].sum += t[t[x].r].sum;
	}
	bool is_root(int x) { return !t[x].p || (t[t[x].p].l ^ x && t[t[x].p].r ^ x); }
	bool is_left(int x) { return t[t[x].p].l == x; }
	void rotate(int x) {
		int p = t[x].p;
		if (is_left(x)) {
			if (t[x].r) t[t[x].r].p = p;
			t[p].l = t[x].r; t[x].r = p;
		}
		else {
			if (t[x].l) t[t[x].l].p = p;
			t[p].r = t[x].l; t[x].l = p;
		}
		if (!is_root(p)) (is_left(p) ? t[t[p].p].l : t[t[p].p].r) = x;
		t[x].p = t[p].p; t[p].p = x;
		update(p); update(x);
	}
	void push(int x) {
		if (t[x].f) {
			if (t[x].l) t[t[x].l].f ^= 1;
		 	if (t[x].r) t[t[x].r].f ^= 1;
			std::swap(t[x].l, t[x].r);
			t[x].f = 0;
		}
	}
	void splay(int x) {
		for (int p; !is_root(x); rotate(x)) {
			p = t[x].p;
			if (!is_root(p)) push(t[p].p);
			push(p); push(x);
			if (is_root(p)) continue;	// zig
			if (is_left(x) == is_left(p)) rotate(p);	// zig-zig
			else rotate(x);	// zig-zag
		}
		push(x);
	}
	void access(int x) {
		splay(x); t[x].r = 0;
		for (int p; t[x].p; splay(x)) {
			p = t[x].p;
			splay(p); t[p].r = x;
		}
	}
	void make_root(int x) {
		access(x);
		t[x].f ^= 1;
	}
	void link(int x, int p) {
		make_root(x); push(x);
		access(p);
		t[p].p = x; t[x].l = p;
	}
	void cut(int x) {
		access(x);
		t[t[x].l].p = 0;
		t[x].l = 0;
	}
	int get_root(int x) {
		access(x);
		while (t[x].l) x = t[x].l;
		splay(x);
		return x;
	}
	int get_parent(int x) {
		access(x);
		if (!(x = t[x].l)) return 0;
		while (t[x].r) x = t[x].r;
		splay(x);
		return x;
	}
	int get_depth(int x) {
		access(x);
		return t[x].l ? t[t[x].l].s : 0;
	}
	int get_lca(int x, int y) {
		access(x); access(y); splay(x);
		return t[x].p ? t[x].p : x;
	}
	int query(int x, int y) {
		int l = get_lca(x, y);
		int result = t[l].v;

		access(x); splay(l);
		if (t[l].r) result += t[t[l].r].sum;

		access(y); splay(l);
		if (t[l].r) result += t[t[l].r].sum;

		return result;
	}

	void update(int x, int d) {
		splay(x);
		t[x].v = d;
		update(x);
	}
} lct;

std::string q;

int main() {
	std::cin >> N;
	for (int i = 1, a; i <= N; ++i) {
		std::cin >> a;
		lct.t[i].s = 1;
		lct.t[i].v = lct.t[i].sum = a;
	}
	memset(p, -1, sizeof p);

	std::cin >> Q;
	for (int i = 0, a, b; i < Q; ++i) {
		std::cin >> q >> a >> b;
		if (q == "bridge") {
			if (join(a, b)) {
				lct.link(a, b);
				std::cout << "yes" << std::endl;
			}
			else std::cout << "no" << std::endl;
		}
		if (q == "penguins") lct.update(a, b);
		if (q == "excursion") {
			if (find(a) ^ find(b)) std::cout << "impossible" << std::endl;
			else std::cout << lct.query(a, b) << std::endl;
		}
	}
}