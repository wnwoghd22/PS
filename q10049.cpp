#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>

typedef long long ll;

const int LEN = 100'010;

int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return true;
}

std::priority_queue<int> pool_x, pool_y;
int xi, yi, posX[LEN + 2], posY[LEN + 2];
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

int hp, vp;
struct Horizontal {
	int l, r, y, i;
	bool operator<(const Horizontal& o) const {
		if (y == o.y) return l < o.l;
		return y < o.y;
	}
} pool_h[LEN];
struct Vertical {
	int y, x, d, i; // y, x, diff
	bool operator<(const Vertical& o) const {
		if (x == o.x) return y < o.y;
		return y < o.y;
	}
} pool_v[LEN << 1];

std::set<int> verts[LEN << 2];
int seg_v[LEN << 2];
int maxY[LEN];

int seg_pos[LEN  << 2];
int add_line(int l, int r, int idx, int s = 0, int e = xi - 1, int i = 1) {
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) {
		if (~seg_v[i]) join(idx, seg_v[i]);
		for (const int& v : verts[i]) {
			join(idx, v);
			if (!~seg_v[i] || maxY[v] > maxY[seg_v[i]])
				seg_v[i] = v;
		}
		verts[i].clear();
		return seg_pos[i];
	}
	int m = s + e >> 1;
	return add_line(l, r, idx, s, m, i << 1) + add_line(l, r, idx, m + 1, e, i << 1 | 1);
}
void update_pos(int x, int d, int idx, int s = 0, int e = xi - 1, int i = 1) {
	if (x < s || e < x) return;

	if (d > 0) verts[i].insert(idx);
	else if (d < 0) {
		verts[i].erase(idx);
		if (seg_v[i] == idx) seg_v[i] = -1;
	}

	if (s == e) {
		seg_pos[i] += d;
		return;
	}
	int m = s + e >> 1;
	update_pos(x, d, idx, s, m, i << 1);
	update_pos(x, d, idx, m + 1, e, i << 1 | 1);
	seg_pos[i] = seg_pos[i << 1] + seg_pos[i << 1 | 1];
}

int N, W, H;
ll V, E, F, chi;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> W >> H >> N;
	pool_x.push(0); pool_x.push(-W);
	pool_y.push(0); pool_y.push(-H); pool_y.push(-H-1);
	for (int i = 0, a, b, c, d; i < N; ++i) {
		std::cin >> a >> b >> c >> d;
		if (a ^ c) // horizontal
			pool_h[hp++] = { a, c, b, i };
		if (b ^ d) { // vertical
			pool_v[vp++] = { b, c, 1, i };
			pool_v[vp++] = { d + 1, c, -1, i };
			maxY[i] = d;
			++d;
		}

		pool_x.push(-a); pool_x.push(-c);
		pool_y.push(-b); pool_y.push(-d);
	}
	pool_h[hp++] = { 0, W, 0, N };
	pool_h[hp++] = { 0, W, H, N };
	pool_v[vp++] = { 0, 0, 1, N };
	pool_v[vp++] = { H + 1, 0, -1, N };
	pool_v[vp++] = { 0, W, 1, N };
	pool_v[vp++] = { H + 1, W, -1, N };

	// compressing
	int x = -1; while (pool_x.size()) { if (-pool_x.top() ^ x) posX[xi++] = x = -pool_x.top(); pool_x.pop(); }
	int y = -1; while (pool_y.size()) { if (-pool_y.top() ^ y) posY[yi++] = y = -pool_y.top(); pool_y.pop(); }

	// std::cout << "compressed:\n";
	// for (int i = 0; i < xi; ++i) std::cout << posX[i] << ' '; std::cout << '\n';
	// for (int i = 0; i < yi; ++i) std::cout << posY[i] << ' '; std::cout << '\n';

	std::sort(pool_h, pool_h + hp);
	std::sort(pool_v, pool_v + vp);
	memset(p, -1, sizeof p);
	memset(seg_v, -1, sizeof seg_v);
	// for (int i = 0; i < hp; ++i) std::cout << "range: " << pool_h[i].y << ' ' << pool_h[i].l << '~' << pool_h[i].r << '\n';
	// for (int i = 0; i < vp; ++i) std::cout << "pos: " << pool_v[i].x << '\n';

	for (int y = 0, i = 0, j = 0; y <= yi; ++y) {
		while (i < vp && getY(pool_v[i].y) == y) {
			// std::cout << "update pos " << y << ", " << pool_v[i].x << ": " << pool_v[i].d << '\n';
			if (pool_v[i].d < 0) ++E; ++V;
			update_pos(getX(pool_v[i].x), pool_v[i].d, pool_v[i].i);
			++i;
		}
		while (j < hp && getY(pool_h[j].y) == y) {
			// std::cout << "update range " << y << ", " << pool_h[j].l << ": " << pool_h[j].r << '\n';
			int crossed = add_line(getX(pool_h[j].l), getX(pool_h[j].r), pool_h[j].i);
			E += crossed * 2 + 1;
			V += crossed + 2;
			++j;
		}
	}
	for (int i = 0; i <= N; ++i) if (i == find(i)) ++chi;
	// std::cout << "V, E, chi = " << V << ',' << E << ',' << chi << '\n';
	F = chi - V + E;
	std::cout << F;
}