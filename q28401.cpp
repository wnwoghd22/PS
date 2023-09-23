#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;

struct Pos {
	ll x, y;
	bool operator<(const Pos& p) const {
		if (x == p.x) return y < p.y;
		return x < p.x;
	}
} p[100'000];

ll cross(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) { return (p2.x - p1.x) * (p4.y - p3.y) - (p2.y - p1.y) * (p4.x - p3.x); }
ll dot(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) { return (p2.x - p1.x) * (p4.x - p3.x) + (p2.y - p1.y) * (p4.y - p3.y); }

void monotone_chain(std::vector<Pos>& p, std::vector<Pos>& hull) {
	std::sort(p.begin(), p.end());
	if (p.size() <= 2) {
		for (const Pos& pos : p) hull.push_back(pos);
		return;
	}
	for (int i = 0; i < p.size(); ++i) {
		while (hull.size() > 1 && cross(hull[hull.size() - 2], hull[hull.size() - 1], hull[hull.size() - 1], p[i]) <= 0) hull.pop_back();
		hull.push_back(p[i]);
	}
	hull.pop_back();
	int s = hull.size() + 1;
	for (int i = p.size() - 1; i >= 0; --i) {
		while (hull.size() > s && cross(hull[hull.size() - 2], hull[hull.size() - 1], hull[hull.size() - 1], p[i]) <= 0) hull.pop_back();
		hull.push_back(p[i]);
	}
	hull.pop_back();
}

bool intersect(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) {
	bool f11 = cross(p1, p2, p2, p3) * cross(p2, p1, p1, p4) > 0;
	bool f12 = cross(p3, p4, p4, p1) * cross(p4, p3, p3, p2) > 0;
	bool line = !cross(p1, p3, p3, p2) && dot(p1, p3, p3, p2) >= 0 ||
		!cross(p1, p4, p4, p2) && dot(p1, p4, p4, p2) >= 0 ||
		!cross(p3, p1, p1, p4) && dot(p3, p1, p1, p4) >= 0 ||
		!cross(p3, p2, p2, p4) && dot(p3, p2, p2, p4) >= 0;
	return f11 && f12 || line;
}

int R, C, X, Y, K;
std::vector<Pos> c1, c2, h1, h2;
Pos u1, u2, d1, d2;

int main() {
	std::cin >> R >> C >> K; X = C, Y = R;
	for (int i = 0; i < K; ++i) std::cin >> p[i].y >> p[i].x;
	d1 = { 2, 1 }; d2 = { X + 1, Y }; u1 = { 1, 2 }; u2 = { X, Y + 1 };
	c1.push_back(d1); c1.push_back(d2);
	c2.push_back(u1); c2.push_back(u2);

	for (int i = 0; i < K; ++i) {
		Pos p1 = { p[i].x + 1, p[i].y }, p2 = { p[i].x, p[i].y + 1 };
		bool i1 = intersect(d1, d2, p1, p2), i2 = intersect(u1, u2, p1, p2);
		if (i1 && i2) { std::cout << 0; return 0; }
		if (i1) { c1.push_back(p2); }
		if (i2) { c2.push_back(p1); }
	}
	monotone_chain(c1, h1);
	monotone_chain(c2, h2);
	for (int i = 0; i < h1.size(); ++i) {
		for (int j = 0; j < h2.size(); ++j) {
			if (intersect(h1[i], h1[(i + 1) % h1.size()], h2[j], h2[(j + 1) % h2.size()])) {
				std::cout << 0; return 0;
			}
		}
	}
	std::cout << 1;
}