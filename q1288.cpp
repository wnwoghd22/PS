#include <iostream>

typedef long double ld;
const int LEN = 100;
const ld TOL = 1e-9;

struct V;
V pivot;

struct V {
	ld x, y;
	V operator+(const V& r) const { return { x + r.x, y + r.y }; }
	V operator*(const ld s) const { return { x * s, y * s }; }
	V operator/(const V& r) const { return { x - r.x, r.y - y }; }
	V operator~() const { return { -y, x }; }
	bool operator<(const V& r) const {
		if (x == pivot.x && r.x == pivot.x) return y < r.y;
		// if (x == pivot.x) return y > pivot.y ? x 
	}
} pos[LEN];
ld dist(const V& p1, const V& p2) { return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y); }
V mid(const V& p1, const V& p2) { return (p1 + p2) * 0.5; }

struct L { V slope; ld c; } lines[105];
L line(const V& s, const V& p) { return { s, s.y * p.x + s.x * p.y }; }
V intersect(const L& l1, const L& l2) {
	ld det = l1.slope.y * l2.slope.x - l1.slope.x * l2.slope.y;
	return { (l1.c * l2.slope.x - l1.slope.x * l2.c) / det, (l1.slope.y * l2.c - l1.c * l2.slope.y) / det };
}

struct P {

};

int N;

int main() {


}