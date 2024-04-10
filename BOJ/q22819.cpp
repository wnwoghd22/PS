#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

typedef long long ll;
typedef double ld;

const ld TOL = 1e-7; // tolerance
const ld PI = acos(-1);

struct Circle {
	ld x, y, r;
	Circle operator-(const Circle& c) const { return { x - c.x, y - c.y, r - c.r }; }
	bool operator!=(const Circle& c) const { return std::abs(x - c.x) >= TOL || std::abs(y - c.y) >= TOL || std::abs(r - c.r) >= TOL; }
	ld H(const ld theta) const { return sin(theta) * x + cos(theta) * y + r; } // coordinate transform(rotate theta) and get top y-intercept
};

struct Arc {
	ld l, r;
	Circle c;
};
typedef std::vector<Arc> Arcs;

inline ld norm(ld theta) {
	while (theta < 0) theta += PI * 2;
	while (theta >= PI * 2) theta -= PI * 2;
	return theta;
}

Arcs merge(const Circle& p, const Circle& q, ld cur, ld next) {
	if (cur >= next) return std::vector<Arc>();
	Circle delta = p - q;
	if (std::abs(delta.x) < TOL && std::abs(delta.y) < TOL) {
		if (delta.r >= 0) return { { cur, next, p } };
		else return { { cur, next, q } };
	}
	ld t = -delta.r / hypot(delta.x, delta.y);
	if (t >= 1) return { { cur, next, q } };
	if (t <= -1) return { { cur, next, p } };

	ld phi = atan2(delta.y, delta.x);
	ld x1 = asin(std::abs(t)) + (t < 0 ? PI : 0);
	ld x2 = PI - x1;
	x1 = norm(x1 - phi);
	x2 = norm(x2 - phi);
	if (x1 > x2) std::swap(x1, x2);

	Arcs h;
	if (p.H((x1 + x2) / 2) < q.H((x1 + x2) / 2))
		h = { { 0, x1, p }, { x1, x2, q }, { x2, 2 * PI, p } };
	else h = { { 0, x1, q }, { x1, x2, p }, { x2, 2 * PI, q } };

	Arcs hull;
	for (const Arc& a : h) {
		ld l = a.l, r = a.r;
		Circle c = a.c;
		l = std::max(l, cur);
		r = std::min(r, next);
		if (l >= r) continue;
		hull.push_back({ l, r, c });
	}
	return hull;
}

Arcs merge(const Arcs& h1, const Arcs& h2) {
	int i = 0, j = 0;
	ld l = 0;
	Arcs h;
	while (i < h1.size() && j < h2.size()) {
		if (h1[i].r < h2[j].r) {
			Arcs a = merge(h1[i].c, h2[j].c, l, h1[i].r);
			l = h1[i++].r;
			for (const Arc& x : a) h.push_back(x);
		}
		else {
			Arcs a = merge(h2[j].c, h1[i].c, l, h2[j].r);
			l = h2[j++].r;
			for (const Arc& x : a) h.push_back(x);
		}
	}
	Arcs hull;
	l = 0;
	for (int i = 0; i < h.size(); ++i) {
		if (i + 1 == h.size() || h[i + 1].c != h[i].c) {
			hull.push_back({ l, h[i].r, h[i].c });
			l = h[i].r;
		}
	}
	return hull;
}

Arcs get_hull(int l, int r, const std::vector<Circle>& c) {
	if (l == r) return { { 0, 2 * PI, c[l] } };
	int m = l + r >> 1;
	return merge(get_hull(l, m, c), get_hull(m + 1, r, c));
}

Arcs get_hull(std::vector<Circle>& c) {
	for (auto& e : c) std::swap(e.x, e.y);
	Arcs hull = get_hull(0, c.size() - 1, c);
	for (auto& e : hull) std::swap(e.c.x, e.c.y);
	return hull;
}

ld get_perimeter(const Arcs& hull) {
	ld ans = 0;
	for (int i = 0; i < hull.size(); ++i) {
		ans += (hull[i].r - hull[i].l) * hull[i].c.r;
		Circle c = hull[i].c - hull[(i + 1) % hull.size()].c;
		ans += sqrt((c.x * c.x + c.y * c.y) - c.r * c.r);
	}
	return ans;
}

int T, N;
std::vector<Circle> C;

bool solve() {
	std::cin >> N;
	if (!N) return 0;
	C.clear();
	for (int i = 0; i < N; ++i) {
		ld x, y, r;
		std::cin >> x >> y >> r;
		C.push_back({ (ld)x, (ld)y, (ld)r });
	}
	std::cout << get_perimeter(get_hull(C)) << '\n';
	return 1;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cout << std::fixed;
	std::cout.precision(9);
	while (solve());
}