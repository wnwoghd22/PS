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
} pos[2], hull[LEN];
const V Zero = { 0, 0 };
ld dist(const V& p1, const V& p2) {
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
ld cross(const V& p1, const V& p2, const V& p3) {
	return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x);
}
void normalize(V& d1, V& d2) { if (cross(Zero, d2, d1) > 0) std::swap(d1, d2); }

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
	if (l1.s * l2.s < 0 + TOL) return 0;
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

bool f(int m) {
	for (int i = 0, j = 0; i < N; ++i)
		if (planes[i].i < m)
			lines[j++] = planes[i];
	if (!half_plane_intersection(m)) return 1;
	for (int i = 0; i < hpi_len; ++i) {
		if (dist(hull[i], Zero) > D * D - TOL) return 1;
	}
	return 0;
}

int binary_search() {
	if (f(N)) return -1;
	int l = 1, r = N, m, ret = 0;
	while (l <= r) {
		m = l + r >> 1;
		if (f(m)) {
			ret = std::max(ret, m);
			l = m + 1;
		}
		else r = m - 1;
	}
	return ret + 1;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> D;
	for (int i = 0; i < N; ++i) {
		std::cin >> pos[0].x >> pos[0].y >> pos[1].x >> pos[1].y;
		normalize(pos[0], pos[1]);
		ld dy = pos[1].y - pos[0].y;
		ld dx = pos[0].x - pos[1].x;
		planes[i] = { { dx, dy }, dy * pos[0].x + dx * pos[0].y, i };
	}
	std::sort(planes, planes + N);
	int ret = binary_search();
	if (~ret) std::cout << ret;
	else std::cout << '*';
}
