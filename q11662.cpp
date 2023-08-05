#include <iostream>
#include <cmath>

typedef long double ld;
const ld ERR = 1e-7;

struct P { ld x, y; } A, B, C, D;

P lerp(const P& s, const P& e, ld alpha) {
	return {
		s.x + (e.x - s.x) * alpha,
		s.y + (e.y - s.y) * alpha
	};
}

ld dist(const P& a, const P& b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }

ld ternary_search() {
	ld l = 0, r = 1, m1, m2, d1, d2;
	while (l < r - ERR) {
		m1 = (l * 2 + r) / 3;
		m2 = (l + r * 2) / 3;
		d1 = dist(lerp(A, B, m1), lerp(C, D, m1));
		d2 = dist(lerp(A, B, m2), lerp(C, D, m2));
		if (d1 < d2) r = m2;
		else l = m1;
	}
	return l;
}

int main() {
	std::cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;
	ld alpha = ternary_search();
	std::cout << std::fixed;
	std::cout.precision(7);
	std::cout << sqrt(dist(lerp(A, B, alpha), lerp(C, D, alpha)));
}