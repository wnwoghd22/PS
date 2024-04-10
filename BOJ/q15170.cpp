#include <iostream>

typedef long double ld;
const int LEN = 100;
const ld TOL = 1e-9;

struct V { 
	ld x, y;
	V operator+(const V& r) const { return { x + r.x, y + r.y }; }
	V operator*(const ld s) const { return { x * s, y * s }; }
	V operator/(const V& r) const { return { x - r.x, r.y - y }; }
	V operator~() const { return { -y, x }; }
} pos[LEN];
ld dist(const V& p1, const V& p2) { return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y); }
V mid(const V& p1, const V& p2) { return (p1 + p2) * 0.5; }
struct L { V slope; ld c; };
L line(const V& s, const V& p) { return { s, s.y * p.x + s.x * p.y }; }
V intersect(const L& l1, const L& l2) {
	ld det = l1.slope.y * l2.slope.x - l1.slope.x * l2.slope.y;
	return { (l1.c * l2.slope.x - l1.slope.x * l2.c) / det, (l1.slope.y * l2.c - l1.c * l2.slope.y) / det };
}
bool check(const L& l1, const L& l2) { return std::abs(l1.slope.y * l2.slope.x - l1.slope.x * l2.slope.y) < TOL; }

struct Circle {
	V c;
	ld sqr; // r square
};

Circle get(const V& p1, const V& p2) { V c = mid(p1, p2); ld r = dist(p1, c); return { c, r }; }
Circle get(const V& p1, const V& p2, const V& p3) {
	V m1 = mid(p1, p2), m2 = mid(p2, p3);
	V s1 = p1 / p2, s2 = p2 / p3;
	L l1 = line(~s1, m1), l2 = line(~s2, m2);
	if (check(l1, l2)) return { (0.0, 0.0), -1 };
	V c = intersect(l1, l2); ld sqr = dist(c, p1);
	return { c, sqr };
}

int N, P[LEN];
char p;

int main() {
	std::cin >> N;
	if (N <= 2) {
		std::cout << "No";
		return 0;
	}
	for (int i = 0; i < N; ++i) {
		std::cin >> pos[i].x >> pos[i].y >> p;
		P[i] = p == 'I';
	}
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			Circle c = get(pos[i], pos[j]);
			bool flag = 1;
			for (int k = 0; k < N; ++k) {
				ld d = dist(pos[k], c.c);
				if (P[k] && d > c.sqr || !P[k] && d < c.sqr) {
					flag = 0;
					break;
				}
			}
			if (flag) {
				// std::cout << i << ' ' << j << '\n';
				std::cout << "No";
				return 0;
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			for (int l = j + 1; l < N; ++l) {
				Circle c = get(pos[i], pos[j], pos[l]);
				if (c.sqr < 0)
					continue;
				bool flag = 1;
				for (int k = 0; k < N; ++k) {
					ld d = dist(pos[k], c.c);
					if (P[k] && d > c.sqr || !P[k] && d < c.sqr) {
						flag = 0;
						break;
					}
				}
				if (flag) {
					// std::cout << i << ' ' << j << ' ' << l <<  '\n';
					std::cout << "No";
					return 0;
				}
			}
		}
	}

	std::cout << "Yes";
}