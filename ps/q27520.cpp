#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cmath>

typedef long long ll;
typedef double ld;
const ld TOL = 1e-7;
const ll LEN = 2e4;

int N;
ld D;
bool z(ld x) { return std::abs(x) < TOL; }
int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

struct V {
	ld x, y;
	V operator-() const { return { -x, -y }; }
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
	ld operator*(const L& o) const { return s * o.s; }
	L operator-() const { return { -s, -c }; }
	L operator+(const ld& scalar) const { return { s, c + hypot(s.x, s.y) * scalar }; }
	bool operator<(const L& o) const {
		bool f1 = Zero < s;
		bool f2 = Zero < o.s;
		if (f1 ^ f2) return f1;
		ld ccw = s * o.s;
		return z(ccw) ? c * hypot(o.s.x, o.s.y) < o.c * hypot(s.x, s.y) : ccw > 0;
	}
} planes[LEN], dq[LEN * 2];
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
int half_plane_intersection(ld m) {
	hpi_len = 0;
	int head = 0, tail = 0;
	for (int i = 0; i < N; ++i) {
		L l = planes[i] + m;
		if (head - tail && z(dq[head - 1] * l)) continue;
		while (head - tail >= 2 && cw(dq[head - 2], dq[head - 1], l)) --head;
		while (head - tail >= 2 && cw(l, dq[tail], dq[tail + 1])) ++tail;
		dq[head++] = l;
	}
	for (int i = 0; i < N; ++i) {
		L l = -planes[i] + m;
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

ld binary_search() {
	ld l = 0, r = 1e12, m, ret = r;
	while (l < r) {
		m = (l + r) / 2;
		if (half_plane_intersection(m)) {
			ret = std::min(ret, m);
			r = m - TOL;
		}
		else l = m + TOL;
	}
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0, a, b, c, d; i < N; ++i) {
		std::cin >> a >> b >> c; c *= -1;
		d = gcd(std::abs(a), std::abs(b));
		ld dx = b / d;
		ld dy = a / d;
		if (dy > 0 || dy == 0 && dx > 0) { dx *= -1; dy *= -1; c *= -1; }
		planes[i] = { { dx, dy }, (ld)c / d };
	}
	std::sort(planes, planes + N);
	ld ret = binary_search();
	std::cout << std::fixed;
	std::cout.precision(7);
	std::cout << ret;
}
