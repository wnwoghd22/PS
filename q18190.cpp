#include <iostream>
#include <vector>

typedef long long ll;
typedef long double ld;
const int LEN = 1e5;

struct Pos { ll x, y; };
ll cross(const Pos& d1, const Pos& d2, const Pos& d3) { return (d2.x - d1.x) * (d3.y - d2.y) - (d2.y - d1.y) * (d3.x - d2.x); }
ll dot(const Pos& d1, const Pos& d2, const Pos& d3) { return (d2.x - d1.x) * (d3.x - d2.x) + (d2.y - d1.y) * (d3.y - d2.y); }
int ccw(const Pos& d1, const Pos& d2, const Pos& d3) {
	ll c = cross(d1, d2, d3);
	return c > 0 ? 1 : c < 0 ? -1 : 0;
}
bool intersect(const Pos& d1, const Pos& d2, const Pos& d3) { return !ccw(d1, d2, d3) && dot(d1, d3, d2) >= 0; }

std::vector<Pos> Ho, Hi;
ll So[LEN], Si[LEN];
int N, M, Q;

int check(const std::vector<Pos>& hull, const Pos& p) {
	int l = 1, r = hull.size() - 1, m, x;
	if (ccw(hull[0], hull[l], p) <= 0) return -1 * !intersect(hull[0], hull[l], p);
	if (ccw(hull[0], hull[r], p) >= 0) return -1 * !intersect(hull[0], hull[r], p);
	while (l < r - 1) {
		m = l + r >> 1;
		x = ccw(hull[0], hull[m], p);
		if (x >= 0) l = m;
		else r = m;
	}
	x = ccw(hull[l], hull[r], p);
	if (x > 0) return x;
	return -1 * !intersect(hull[l], hull[r], p);
}

int get_bound(const std::vector<Pos>& h, const Pos& p, int s, int e, bool f) {
	while (s < e) {
		int m = s + e >> 1;
		Pos pp = p, cur = h[m], nxt = h[(m + 1) % h.size()];
		if (!f) std::swap(pp, cur);
		if (ccw(pp, cur, nxt) > 0) s = m + 1;
		else e = m;
	}
	return s;
}

ll get_inner(const Pos& p, int& l, int& r) {
	l = 0, r = 0;
	int ccw1 = ccw(p, Hi[0], Hi[1]), ccwN = ccw(p, Hi[0], Hi[M - 1]);

	if (ccw1 * ccwN >= 0) {
		if (!ccw1 && dot(p, Hi[1], Hi[0]) > 0) l = 1;
		if (!ccwN && dot(p, Hi[M - 1], Hi[0]) > 0) l = M - 1;
		int s = 0 + !ccw1, e = M - 1 - !ccwN;
		bool f = ccw(p, Hi[s], Hi[s + 1]) >= 0;
		r = get_bound(Hi, p, s, e, f);
		if (!ccw(p, Hi[r], Hi[(r + 1) % M]) && dot(p, Hi[(r + 1) % M], Hi[r]) > 0) r = (r + 1) % M;
	}
	else {
		int s = 0, e = M - 1, m, x;
		bool f = ccw1 > 0 && ccwN < 0;
		while (s < e - 1) {
			m = s + e >> 1;
			x = ccw(Hi[0], Hi[m], p);
			if (!f) x *= -1;
			if (x > 0) s = m;
			else e = m;
		}
		l = get_bound(Hi, p, 0, s, f);
		if (!ccw(p, Hi[l], Hi[(l + 1) % M]) && dot(p, Hi[(l + 1) % M], Hi[l]) > 0) l = (l + 1) % M;

		r = get_bound(Hi, p, e, M - 1, !f);
		if (!ccw(p, Hi[r], Hi[(r + 1) % M]) && dot(p, Hi[(r + 1) % M], Hi[r]) > 0) r = (r + 1) % M;
	}

	if (l > r) std::swap(l, r);
	ll area = Si[r] - Si[l] - cross(Hi[0], Hi[l], Hi[r]);
	ll tri = cross(p, Hi[l], Hi[r]);
	if (tri < 0) area = Si[M - 1] - area - tri, std::swap(l, r);
	else area += tri;
	// std::cout << "in: " << l << ' ' << r << ' ' << area << ' ' << tri << '\n';
	return area;
}

ld get_outer(const Pos& p, int& l, int& r, const int li, const int ri) {
	l = 0, r = 0;
	int s = 0, e = N - 1, m;
	ld wing_l = 0, wing_r = 0;
	const Pos& pl = Hi[li];
	const Pos& pr = Hi[ri];

	while (s < e - 1) {
		m = s + e >> 1;
		if (ccw(Ho[0], Ho[m], p) >= 0) s = m;
		else e = m;
	}
	int sl = 0, el = 0;
	if (ccw(p, Ho[s], pl) >= 0 && ccw(p, Ho[e], pl) <= 0) { // between s and e
		sl = s, el = e;
	}
	else {
		if (ccw(Ho[0], p, pl) < 0) sl = 0, el = s;
		if (ccw(Ho[0], p, pl) > 0) sl = e, el = N;
		while (sl < el - 1) {
			m = sl + el >> 1;
			if (ccw(p, Ho[m % N], pl) > 0) sl = m;
			else el = m;
		}
	}
	sl %= N, el %= N; l = sl;
	if (cross(p, pl, Ho[l])) {
		ll tril = std::abs(cross(p, Ho[sl], Ho[el]));
		ll al = std::abs(cross(p, pl, Ho[sl]));
		ll bl = std::abs(cross(p, pl, Ho[el]));
		wing_l = tril * ((ld)al / (al + bl));
	}

	int sr = 0, er = 0;
	if (ccw(p, Ho[s], pr) >= 0 && ccw(p, Ho[e], pr) <= 0) { // between s and e
		sr = s, er = e;
	}
	else {
		if (ccw(Ho[0], p, pr) < 0) sr = 0, er = s;
		if (ccw(Ho[0], p, pr) > 0) sr = e, er = N;
		while (sr < er - 1) {
			m = sr + er >> 1;
			if (ccw(p, Ho[m % N], pr) > 0) sr = m;
			else er = m;
		}
	}
	sr %= N, er %= N; r = er;
	if (cross(p, pr, Ho[r])) {
		ll trir = std::abs(cross(p, Ho[sr], Ho[er]));
		ll ar = std::abs(cross(p, pr, Ho[sr]));
		ll br = std::abs(cross(p, pr, Ho[er]));
		wing_r = trir * ((ld)br / (ar + br));
	}

	bool f = l > r;
	ll tri = cross(Ho[l], Ho[r], p);
	if (f) std::swap(l, r);
	ll area = So[r] - So[l] - cross(Ho[0], Ho[l], Ho[r]);
	if (f) area = So[N - 1] - area;

	area += tri;

	// std::cout << f << ' ' << tri << '\n';

	// std::cout << sl << ' ' << el << ' ' << sr << ' ' << er << '\n';
	// std::cout << "outer: " << area << " - " << wing_l << " - " << wing_r << " = " << area - (wing_l + wing_r) << '\n';

	return area - (wing_l + wing_r);
}

ld get_area(const Pos& p) {
	int li, ri, lo, ro;
	// std::cout << "in\n";
	ll inner = get_inner(p, li, ri);
	// std::cout << "out\n";
	ld outer = get_outer(p, lo, ro, li, ri);

	// std::cout << "inner: " << inner << '\n';

	return (outer - inner) * 0.5l;
}


int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cout << std::fixed;
	std::cout.precision(7);
	std::cin >> N >> M >> Q;
	for (int i = 0, x, y; i < N; ++i) {
		std::cin >> x >> y;
		Ho.push_back({ x, y });
	}
	for (int i = 2; i < N; ++i) {
		So[i] = cross(Ho[0], Ho[i - 1], Ho[i]);
		So[i] = So[i] + So[i - 1];
	}
	for (int i = 0, x, y; i < M; ++i) {
		std::cin >> x >> y;
		Hi.push_back({ x, y });
	}
	for (int i = 2; i < M; ++i) {
		Si[i] = cross(Hi[0], Hi[i - 1], Hi[i]);
		Si[i] = Si[i] + Si[i - 1];
	}

	for (int i = 0, x, y; i < Q; ++i) {
		std::cin >> x >> y;
		Pos p = { x, y };

		if (check(Ho, p) <= 0) std::cout << "OUT\n";
		else if (check(Hi, p) >= 0) std::cout << "IN\n";
		else std::cout << get_area(p) << '\n';
	}
}