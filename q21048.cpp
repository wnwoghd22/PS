#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <cmath>

typedef long long ll;
typedef long double ld;
const ld TOL = 1e-9;
const ll LEN = 5e4;

int N;
bool z(ld x) { return std::abs(x) < TOL; }

struct V {
	ld x, y;
	ld operator*(const V& o) const { return y * o.x - x * o.y; }
	bool operator<(const V& o) const { return z(y - o.y) ? x < o.x : y < o.y; }
} pos[LEN];
const V Zero = { 0, 0 };
ld cross(const V& p1, const V& p2, const V& p3) {
	return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x);
}
ld area(const std::vector<V>& H) {
	int l = H.size();
	ld a = 0;
	for (int i = 0; i < l; ++i)
		a += cross(Zero, H[i], H[(i + 1) % l]);
	return a / 2;
}

struct L {
	V s; // slope
	ld c;
	ld operator*(const L& o) const { return s * o.s; }
	bool operator<(const L& o) const {
		bool f1 = Zero < s;
		bool f2 = Zero < o.s;
		if (f1 ^ f2) return f1;
		ld ccw = s * o.s;
		return z(ccw) ? c * hypot(o.s.x, o.s.y) < o.c * hypot(s.x, s.y) : ccw > 0;
	}
};
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

bool half_plane_intersection(std::vector<L>& lines, std::vector<V>& hull) {
	std::deque<L> dq;
	std::sort(lines.begin(), lines.end());
	for (const L& l : lines) {
		if (dq.size() && z(dq.back() * l)) continue;
		while (dq.size() >= 2 && cw(dq[dq.size() - 2], dq.back(), l)) dq.pop_back();
		while (dq.size() >= 2 && cw(l, dq.front(), dq[1])) dq.pop_front();
		dq.push_back(l);
	}
	while (dq.size() >= 3 && cw(dq[dq.size() - 2], dq.back(), dq.front())) dq.pop_back();
	while (dq.size() >= 3 && cw(dq.back(), dq.front(), dq[1])) dq.front();

	for (int i = 0; i < dq.size(); ++i) {
		L  cur = dq[i], nxt = dq[(i + 1) % dq.size()];
		if (cur * nxt < TOL) {
			hull.clear();
			return 0;
		}
		hull.push_back(intersect(cur, nxt));
	}
	return 1;
}

bool f(int m) {
	std::vector<L> lines;
	ld dx, dy, c;
	for (int i = 0, j = m; i < N; ++i, j = (j + 1) % N) {
		dx = pos[i].x - pos[j].x;
		dy = pos[j].y - pos[i].y;
		c = dy * pos[i].x + dx * pos[i].y;
		lines.push_back({ { dx, dy }, c });
	}
	std::vector<V> hull;
	if (!half_plane_intersection(lines, hull)) return 0;
	ld a = area(hull);
	return !z(a);
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cout << std::fixed;
	std::cout.precision(7);
	std::cin >> N;
	for (int i = N - 1; i >= 0; --i) std::cin >> pos[i].x >> pos[i].y;
	std::vector<L> lines;
	ld dx, dy, c;
	for (int i = 0, j = 1; j < N; ++i, ++j) {
		dx = pos[i].x - pos[j].x;
		dy = pos[j].y - pos[i].y;
		c = dy * pos[i].x + dx * pos[i].y;
		lines.push_back({ { dx, dy }, c });
	}
	dx = pos[N - 1].x - pos[0].x;
	dy = pos[0].y - pos[N - 1].y;
	c = dy * pos[0].x + dx * pos[0].y;
	lines.push_back({ { dx, dy }, c });

	std::vector<V> hull;
	if (!half_plane_intersection(lines, hull)) std::cout << 0;
	else std::cout << area(hull);
}