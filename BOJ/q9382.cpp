#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cmath>

typedef long double ld;
const ld INF = 1e17;
const ld TOL = 1e-7;
const int LEN = 1e6;

int N;
ld R;

struct Pos { 
	ld x, y;
	Pos operator+(const Pos& p) const { return { x + p.x, y + p.y }; }
	Pos operator-(const Pos& p) const { return { x - p.x, y - p.y }; }
	Pos operator*(ld scalar) const { return { x * scalar, y * scalar }; }
	Pos operator/(ld scalar) const { return { x / scalar, y / scalar }; }
} circle[100], candidates[LEN];
const Pos zero = { 0, 0 };

ld distance(const Pos& a, const Pos& b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }

ld solve(int n, ld r) {
	N = 0;
	R = r * 2;
	candidates[N++] = { 0, 0 };
	for (int i = 0; i < n; ++i) {
		std::cin >> circle[i].x >> circle[i].y;
		ld d = distance(circle[i], zero);
		if (distance(circle[i], zero) < TOL) candidates[N++] = { 0, R };
		else { // find closest point from circle
			ld ds = sqrtl(d);
			Pos v = circle[i] / ds * R;
			Pos p1 = circle[i] + v;
			Pos p2 = circle[i] - v;
			ld d1 = distance(p1, zero), d2 = distance(p2, zero);
			if (d1 < d2) candidates[N++] = p1;
			else candidates[N++] = p2;
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			ld d = distance(circle[i], circle[j]);
			if (d < TOL || d > R * R * 4) continue; // if two circle are same or too far to intersect, then ignore

			Pos mid = (circle[i] + circle[j]) / 2;
			// std::cout << "mid: " << mid.x << ' ' << mid.y << '\n';

			Pos w = mid - circle[i];
			// std::cout << "w: " << w.x << ' ' << w.y << '\n';

			Pos v = { -w.y, w.x };
			ld mw = distance(w, zero);
			ld mv = R * R - mw;
			v = v / sqrtl(mw) * sqrtl(mv);

			Pos p1 = mid + v;
			Pos p2 = mid - v;
			// std::cout << "p1: " << p1.x << ' ' << p1.y << '\n';
			// std::cout << "p2: " << p2.x << ' ' << p2.y << '\n';
			candidates[N++] = p1;
			candidates[N++] = p2;
		}
	}

	ld result = INF;
	// std::cout << N << '\n';
	for (int i = 0; i < N; ++i) {
		bool flag = true;
		for (int j = 0; j < n; ++j) {
			// std::cout << candidates[i].x << ' ' << candidates[i].y << '\n';
			if (distance(candidates[i], circle[j]) < R * R - TOL * 100) {
				flag = false;
				break;
			}
		}
		if (flag) result = std::min(result, sqrtl(distance(candidates[i], zero)));
	}

	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cout << std::fixed;
	std::cout.precision(6);
	int n;
	ld r;
	while (1) {
		std::cin >> n >> r;
		if (!n && r < TOL) break;
		std::cout << solve(n, r) << '\n';
	}
}