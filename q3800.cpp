#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cmath>

typedef long long ll;
typedef long double ld;
const ld TOL = 1e-9;
const ll LEN = 2e5;

int N;
ld D;
bool z(ld x) { return std::abs(x) < TOL; }

struct V {
	ld x, y;
	ld operator*(const V& o) const { return y * o.x - x * o.y; }
	bool operator<(const V& o) const { return z(y - o.y) ? x < o.x : y < o.y; }
} pos[LEN], hull[LEN];
const V Zero = { 0, 0 };
ld dist(const V& p1, const V& p2) {
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
ld cross(const V& p1, const V& p2, const V& p3) {
	return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x);
}
void normalize(V& d1, V& d2) { if (cross(Zero, d2, d1) > 0) std::swap(d1, d2); }
ld area(int n) {
	ld a = 0;
	for (int i = 0; i < n - 1; ++i)
		a += cross(Zero, hull[i], hull[i + 1]);
	a += cross(Zero, hull[n - 1], hull[0]);
	return a / 2;
}

struct L {
	V s; // slope
	ld c;
	int i;
	ld operator*(const L& o) const { return s * o.s; }
	bool operator<(const L& o) const {
		bool f1 = Zero < s;
		bool f2 = Zero < o.s;
		if (f1 ^ f2) return f1;
		ld ccw = s * o.s;
		return z(ccw) ? c * hypot(o.s.x, o.s.y) < o.c * hypot(s.x, s.y) : ccw > 0;
	}
} lines[LEN], planes[LEN], dq[LEN];
L line(const V& s, const V& p) { return { s, s.y * p.x + s.x * p.y }; }
V intersect(const L& l1, const L& l2) {
	ld det = l1.s * l2.s;
	return { (l1.c * l2.s.x - l1.s.x * l2.c) / det, (l1.s.y * l2.c - l1.c * l2.s.y) / det };
}

bool cw(const L& l1, const L& l2, const L& target) {
	if (l1.s* l2.s < 0 + TOL) return 0;
	V p = intersect(l1, l2);
	return target.s.y * p.x + target.s.x * p.y > target.c - TOL;
}

int hpi_len;
int half_plane_intersection(int n) {
	hpi_len = 0;
	int head = 0, tail = 0;
	for (int i = 0; i < n; ++i) {
		L l = lines[i];
		if (head - tail && z(dq[head - 1] * l)) continue;
		while (head - tail >= 2 && cw(dq[head - 2], dq[head - 1], l)) --head;
		while (head - tail >= 2 && cw(l, dq[tail], dq[tail + 1])) ++tail;
		dq[head++] = l;
	}
	while (head - tail >= 3 && cw(dq[head - 2], dq[head - 1], dq[tail])) --head;
	while (head - tail >= 3 && cw(dq[head - 1], dq[tail], dq[tail + 1])) ++tail;

	for (int i = tail; i < head; ++i) {
		L  cur = dq[i], nxt = dq[i == head - 1 ? tail : i + 1];
		if (cur * nxt < TOL) {
			return hpi_len = 0;
		}
		hull[hpi_len++] = intersect(cur, nxt);
	}
	return hpi_len;
}

ld solve() {
	std::cin >> N;
	for (int i = N - 1; i >= 0; --i)
		std::cin >> pos[i].x >> pos[i].y;
	ld dx, dy, c;
	for (int i = 0, j = 1; j < N; ++i, ++j) {
		dx = pos[i].x - pos[j].x;
		dy = pos[j].y - pos[i].y;
		c = dy * pos[i].x + dx * pos[i].y;

		lines[i] = { { dx, dy }, c };
	}
	dx = pos[N - 1].x - pos[0].x;
	dy = pos[0].y - pos[N - 1].y;
	c = dy * pos[0].x + dx * pos[0].y;
	lines[N - 1] = { { dx, dy }, c };
	std::sort(lines, lines + N);
	if (!half_plane_intersection(N)) return 0;
	return area(hpi_len);
}

int main() {
	int T;
	std::cin.tie(0)->sync_with_stdio(0); 
	std::cout << std::fixed;
	std::cout.precision(2);
	
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';
}