#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
typedef long double ld;
inline ld _abs(ld x) { return x > 0 ? x : -x; }

const ld ERR = 1e-10;

struct Line {
	ld a, b, x;
	int i;
	Line() {}
	Line(ld a, ld b, ld x, int i) : a(a), b(b), x(x), i(i) {}
	bool operator<(const Line& r) {
		if (_abs(a - r.a) < ERR) return b < r.b;
		return a > r.a;
	}
	ld operator&(const Line& r) { return (r.b - b) / (a - r.a); } // get pos X of intersect of l and r
};

ld minX, maxX;
int N, M;

std::vector<Line> lines;
std::vector<Line> hull;

void add_line(Line& l) {
	if (hull.empty()) {
		hull.push_back(l);
		return;
	}
	if (_abs(hull.back().a - l.a) < ERR && l.b > hull.back().b) return;
	while (hull.size() > 1) {
		if (hull.back().x > (hull.back() & l)) hull.pop_back();
		else break;
	}
	l.x = hull.back() & l;
	hull.push_back(l);
}
int binary_search(ld x) {
	int l = 0, r = hull.size() - 1;
	int result = 0, mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (hull[mid].x < x + ERR) {
			result = std::max(result, mid);
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return hull[result].i;
}

int main() {
	freopen("input.txt", "r", stdin);
	// std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> maxX >> minX >> N;
	ld dx = maxX - minX;
	for (int i = 1; i <= N; ++i) {
		ld upY, lowY;
		std::cin >> upY >> lowY;
		ld dy = upY - lowY;
		ld a = dy / dx;
		ld b = lowY - a * minX;
		lines.push_back(Line(a, b, minX, i));
	}
	std::sort(lines.begin(), lines.end());
	for (Line& l : lines) add_line(l);
	std::cin >> M;
	while (M--) {
		std::cin >> dx;
		std::cout << binary_search(dx) << '\n';
	}
}