#include <iostream>
#include <cstring>

typedef long long ll;
const int LEN = 300'001;

int T, N, M;

struct Result { int max, max_i; };

struct LinkCutTree {
	struct Node {
		int l, r, p;
		int s; // size
		bool f; // flip
		int v, max, max_i;
	} t[LEN];
	void update(int x) {
		t[x].s = 1;
		t[x].max = t[x].v;
		t[x].max_i = x;
		if (t[x].l) {
			t[x].s += t[t[x].l].s;
			if (t[t[x].l].max > t[x].max) {
				t[x].max = t[t[x].l].max;
				t[x].max_i = t[t[x].l].max_i;
			}
		}
		if (t[x].r) {
			t[x].s += t[t[x].r].s;
			if (t[t[x].r].max > t[x].max) {
				t[x].max = t[t[x].r].max;
				t[x].max_i = t[t[x].r].max_i;
			}
		}
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
	void cut(int x, int y) {
		if (get_parent(x) == y) cut(x);
		else cut(y);
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
	Result query(int x, int y) {
		int l = get_lca(x, y);
		Result result = { t[l].max, t[l].max_i };

		access(x); splay(l);
		if (t[l].r) {
			if (t[t[l].r].max > result.max) {
				result.max = t[t[l].r].max;
				result.max_i = t[t[l].r].max_i;
			}
		}

		access(y); splay(l);
		if (t[l].r) {
			if (t[t[l].r].max > result.max) {
				result.max = t[t[l].r].max;
				result.max_i = t[t[l].r].max_i;
			}
		}

		return result;
	}

	void update(int x, int d) {
		splay(x);
		t[x].v = d;
		update(x);
	}
} lct;

struct Edge { int u, v; } edges[LEN];

ll solve() {
	ll answer = 0, mst = 0;
	memset(lct.t, 0, sizeof lct.t);

	std::cin >> N >> M;
	for (int i = 2, u, c; i <= N; ++i) {
		std::cin >> u >> c; ++u;
		lct.t[N + i].max_i = N + i;
		lct.t[N + i].v = lct.t[N + i].max = c;
		lct.link(i, N + i);
		lct.link(N + i, u);
		edges[N + i] = { i, u };
		mst += c;
	}

	for (int j = 1, u, v, c; j <= M; ++j) {
		std::cin >> u >> v >> c; ++u, ++v;
		if (u == v) {
			answer ^= mst;
			continue;
		}
		lct.t[N * 2 + j].max_i = N * 2 + j;
		lct.t[N * 2 + j].v = lct.t[N * 2 + j].max = c;
		edges[N * 2 + j] = { u, v };

		Result cur = lct.query(u, v);
		if (c < cur.max) {
			mst += c - cur.max;
			lct.cut(edges[cur.max_i].u, cur.max_i);
			lct.cut(edges[cur.max_i].v, cur.max_i);
			lct.link(u, N * 2 + j);
			lct.link(N * 2 + j, v);
		}
		// std::cout << mst << '\n';
		answer ^= mst;
	}
	return answer;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--)
		std::cout << solve() << '\n';
}