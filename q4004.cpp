#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <map>

typedef long long ll;
enum Slope { LR, UD, LU, LD, RU, RD, };
enum Dir { R, U, L, D, };
int adj[4][4] = {
//	 R   U   L   D
	-1, RU, LR, RD, // R
	RU, -1, LU, UD, // U
	LR, LU, -1, LD, // L
	RD, RU, LD, -1  // D
};

const int LEN = 100'001;
std::map<int, int> slopes[6];
struct Kunai {
	int x, y, d, stamp;
	bool operator<(const Kunai& r) const {
		if (y == r.y) return x < r.x;
		return y < r.y;
	}
} kunais[LEN];

int ptr[LEN][6]; // node index of linked list
struct Node { int bf, nx, i; } ls[LEN * 3];
int ni;

struct Collision {
	int bf, nx, stamp;
	bool operator<(const Collision& r) const { return stamp > r.stamp; }
};
std::priority_queue<Collision> pq;

int dist(int a, int b) { return abs(kunais[a].x - kunais[b].x) + abs(kunais[a].y - kunais[b].y); } // manhatten
int get_key(int slope, int i) {
	switch (slope) {
	case LR: return kunais[i].y;
	case UD: return kunais[i].x;
	case LU: case RD: return kunais[i].y + kunais[i].x;
	case RU: case LD: return kunais[i].y - kunais[i].x;
	}
}
bool isCollide(int slope, int bf, int nx) {
	if (!~bf || !~nx) return false;
	switch (slope) {
	case LR: return kunais[bf].d == R && kunais[nx].d == L;
	case UD: return kunais[bf].d == D && kunais[nx].d == U;
	case LU: return kunais[bf].d == L && kunais[nx].d == U;
	case LD: return kunais[bf].d == D && kunais[nx].d == L;
	case RU: return kunais[bf].d == R && kunais[nx].d == U;
	case RD: return kunais[bf].d == D && kunais[nx].d == R;
	}
}
void push(int slope, int i) {
	int key = get_key(slope, i);
	ptr[i][slope] = ni;
	ls[ni].i = i;
	if (slopes[slope].find(key) != slopes[slope].end()) {
		int bf = slopes[slope][key];
		int bi = ls[bf].i;
		ls[bf].nx = ni;
		ls[ni].bf = bf;
		if (isCollide(slope, bi, i)) {
			// std::cout << "collide: " << i << ", " << bi << '\n';
			pq.push({ bi, i, dist(i, bi) });
		}
	}
	slopes[slope][key] = ni++; // move head
}
void pop(int i) {
	for (int s = 0; s < 6; ++s) {
		if (!~ptr[i][s]) continue;
		Node n = ls[ptr[i][s]];
		if (~n.bf) ls[n.bf].nx = n.nx;
		if (~n.nx) ls[n.nx].bf = n.bf;
		if (~n.bf && ~n.nx && isCollide(s, ls[n.bf].i, ls[n.nx].i)) {
			pq.push({ ls[n.bf].i, ls[n.nx].i, dist(ls[n.bf].i, ls[n.nx].i) });
		}
	}
}

int xi, yi, pool_x[LEN + 2] = { 1, }, pool_y[LEN + 2] = { 1, }, posX[LEN + 2], posY[LEN + 2];
int getX(int x) {
	int l = 0, r = xi - 1, m;
	while (l <= r) {
		m = l + r >> 1;
		if (posX[m] == x) return m;
		else if (posX[m] > x) r = m - 1;
		else l = m + 1;
	}
	return -1;
}
int getY(int y) {
	int l = 0, r = yi - 1, m;
	while (l <= r) {
		m = l + r >> 1;
		if (posY[m] == y) return m;
		else if (posY[m] > y) r = m - 1;
		else l = m + 1;
	}
	return -1;
}

int hi, vi, hp, vp;
struct Horizontal {
	int l, r, y;
	bool operator<(const Horizontal& o) const {
		if (y == o.y) return l < o.l;
		return y < o.y;
	}
} pool_h[LEN * 3], sweeped_h[LEN * 3];
struct Vertical { 
	int u, d, x;
	bool operator<(const Vertical& o) const {
		if (x == o.x) return u < o.u;
		return x < o.x;
	}
} pool_v[LEN * 3];
struct QueryPos {
	int x, y, d;
	bool operator<(const QueryPos& r) const { return y < r.y; }
} queries[LEN * 2];

int seg_pos[LEN * 4];
int seg_count[LEN * 4];
void update_line(int l, int r, int d, int s = 0, int e = xi - 1, int i = 1) {
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		seg_count[i] += d * seg_pos[i];
		return;
	}
	int m = s + e >> 1;
	update_line(l, r, d, s, m, i << 1);
	update_line(l, r, d, m + 1, e, i << 1 | 1);
	seg_count[i] = seg_count[i << 1] + seg_count[i << 1 | 1];
}
void update_pos(int x, int d, int s = 0, int e = xi - 1, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) {
		seg_pos[i] += d;
		return;
	}
	int m = s + e >> 1;
	update_pos(x, d, s, m, i << 1);
	update_pos(x, d, m + 1, e, i << 1 | 1);
	seg_pos[i] = seg_pos[i << 1] + seg_pos[i << 1 | 1];
}

int N, W, H;

ll solve() {
	std::cin >> W >> H >> N;
	ni = 0;
	memset(kunais, -1, sizeof kunais);
	memset(ptr, -1, sizeof ptr);
	memset(ls, -1, sizeof ls);
	for (int i = 0; i < 6; ++i) slopes[i].clear();
	for (int i = 0, x, y, k, d; i < N; ++i) {
		std::cin >> kunais[i].x >> kunais[i].y >> kunais[i].d;
		pool_x[i + 1] = kunais[i].x; pool_y[i + 1] = kunais[i].y;
	}
	pool_x[N + 1] = W; pool_y[N + 1] = H;
	// compressing
	std::sort(pool_x, pool_x + N + 2);
	std::sort(pool_y, pool_y + N + 2);
	for (int i = 0, x = -1; i < N + 2; ++i) if (pool_x[i] ^ x) posX[xi++] = x = pool_x[i];
	for (int i = 0, y = -1; i < N + 2; ++i) if (pool_y[i] ^ y) posY[yi++] = y = pool_y[i];
	std::cout << "compressed:\n";
	for (int i = 0; i < xi; ++i) std::cout << posX[i] << ' '; std::cout << '\n';
	for (int i = 0; i < yi; ++i) std::cout << posY[i] << ' '; std::cout << '\n';

	// simulation step: O(N log N)
	std::sort(kunais, kunais + N);
	for (int i = 0; i < N; ++i) {
		switch (kunais[i].d) {
		case U: push(UD, i); push(LU, i); push(RU, i); break;
		case D: push(UD, i); push(LD, i); push(RD, i); break;
		case L: push(LR, i); push(LU, i); push(LD, i); break;
		case R: push(LR, i); push(RU, i); push(RD, i); break;
		}
	}
	while (pq.size()) {
		Collision c = pq.top(); pq.pop(); // fastest collision
		if (!~kunais[c.bf].stamp && !~kunais[c.nx].stamp) { // new collision
			kunais[c.bf].stamp = kunais[c.nx].stamp = c.stamp;
			pop(c.bf); pop(c.nx);
		}
		else if (!~kunais[c.bf].stamp) {
			if (kunais[c.nx].stamp == c.stamp) { // collides at one point
				kunais[c.bf].stamp = c.stamp;
				pop(c.bf);
			}
			else continue;
		}
		else if (!~kunais[c.nx].stamp) {
			if (kunais[c.bf].stamp == c.stamp) { // collides at one point
				kunais[c.nx].stamp = c.stamp;
				pop(c.nx);
			}
			else continue;
		}
		else continue;

		// get Line
		switch (adj[kunais[c.bf].d][kunais[c.nx].d]) {
		case LR: 
			pool_h[hp++] = { kunais[c.bf].x, kunais[c.nx].x, kunais[c.bf].y };
			break;
		case UD:
			pool_v[vp++] = { kunais[c.bf].y, kunais[c.nx].y, kunais[c.bf].x };
			break;
		case LU:
			pool_h[hp++] = { kunais[c.nx].x, kunais[c.bf].x, kunais[c.bf].y };
			pool_v[vp++] = { kunais[c.bf].y, kunais[c.nx].y, kunais[c.nx].x };
			break;
		case LD:
			pool_h[hp++] = { kunais[c.bf].x, kunais[c.nx].x, kunais[c.nx].y };
			pool_v[vp++] = { kunais[c.bf].y, kunais[c.nx].y, kunais[c.bf].x };
			break;
		case RU:
			pool_h[hp++] = { kunais[c.bf].x, kunais[c.nx].x, kunais[c.bf].y };
			pool_v[vp++] = { kunais[c.bf].y, kunais[c.nx].y, kunais[c.nx].x };
			break;
		case RD:
			pool_h[hp++] = { kunais[c.nx].x, kunais[c.bf].x, kunais[c.nx].y };
			pool_v[vp++] = { kunais[c.bf].y, kunais[c.nx].y, kunais[c.bf].x };
			break;
		}
	}
	for (int i = 0; i < N; ++i) {
		if (!~kunais[i].stamp) { // never collides
			switch (kunais[i].d) {
			case R: pool_h[hp++] = { kunais[i].x, W, kunais[i].y }; break;
			case L: pool_h[hp++] = { 1, kunais[i].x, kunais[i].y }; break;
			case U: pool_v[vp++] = { 1, kunais[i].y, kunais[i].x }; break;
			case D: pool_v[vp++] = { kunais[i].y, H, kunais[i].x }; break;
			}
		}
	}

	// area sweeping step: O(N log N)
	std::sort(pool_h, pool_h + hp);
	std::sort(pool_v, pool_v + vp);
	ll area_h = 0, area_v = 0;
	for (int i = 1, l = pool_h[0].l, r = pool_h[0].r, y = pool_h[0].y; i < hp; ++i) {
		if (pool_h[i].y ^ y) {
			area_h += r - l + 1;
			sweeped_h[hi++] = { getX(l), getX(r), getY(y) };
			y = pool_h[i].y; l = pool_h[i].l; r = pool_h[i].r;
		}
		else {
			if (pool_h[i].l > r + 1) { // new line
				area_h += r - l + 1;
				sweeped_h[hi++] = { getX(l), getX(r), getY(y) };
				l = pool_h[i].l; r = pool_h[i].r;
			}
			else r = std::max(r, pool_h[i].r);
		}
		if (i == hp - 1) {
			area_h += r - l + 1;
			sweeped_h[hi++] = { getX(l), getX(r), getY(y) };
		}
	}
	for (int i = 1, u = pool_v[0].u, d = pool_v[0].d, x = pool_v[0].x; i < vp; ++i) {
		if (pool_v[i].x ^ x) {
			area_v += d - u + 1;
			queries[vi++] = { getX(x), getY(u), 1 };
			queries[vi++] = { getX(x), getY(d) + 1, -1 };
			x = pool_v[i].x; u = pool_v[i].u; d = pool_v[i].d;
		}
		else {
			if (pool_v[i].u > d + 1) { // new line
				area_v += d - u + 1;
				queries[vi++] = { getX(x), getY(u), 1 };
				queries[vi++] = { getX(x), getY(d) + 1, -1 };
				u = pool_v[i].u; d = pool_v[i].d;
			}
			else d = std::max(d, pool_v[i].d);
		}
		if (i == vp - 1) {
			area_v += d - u + 1;
			queries[vi++] = { getX(x), getY(u), 1 };
			queries[vi++] = { getX(x), getY(d) + 1, -1 };
		}
	}
	for (int i = 0; i < vi; ++i) {
		std::cout << "query[" << i << "] = " << queries[i].x << ", " << queries[i].y << ", " << queries[i].d << '\n';
	}

	// check crossing points using segment tree(plane sweeping): O(N log N)
	ll crossed = 0;
	std::vector<Horizontal> stack;
	std::sort(queries, queries + vi);
	for (int y = 0, i = 0, j = 0; y <= yi; ++y) {
		while (i < vi && queries[i].y == y) {
			std::cout << "update pos " << y << ", " << queries[i].x << ": " << queries[i].d << '\n';
			update_pos(queries[i].x, queries[i].d);
			++i;
		}
		while (j < hi && sweeped_h[j].y == y) {
			stack.push_back(sweeped_h[j]);
			update_line(sweeped_h[j].l, sweeped_h[j].r, 1);
			++j;
		}
		crossed += seg_count[1];
		for (const Horizontal& h : stack) {
			update_line(h.l, h.r, -1);
		}
		stack.clear();
	}
	std::cout << "horizontal: " << area_h << '\n';
	std::cout << "vertical: " << area_v << '\n';
	std::cout << "crossed: " << crossed << '\n';

	return area_h + area_v - crossed;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cout << solve();
}