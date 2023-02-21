#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef long double ld;
const ld INF = 2e17;
const ld ERR = 1e-10;
struct Pos { ld x, y; } hull[100], routers[100], points[100];
int K, n, r, p;

ld distance(const Pos& p1, const Pos& p2) {
	return pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);
}

ld cross(const Pos& p1, const Pos& p2, const Pos& p3) {
	return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
}

bool intersect(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) {
	ld v1 = cross(p1, p3, p4);
	ld v2 = cross(p2, p3, p4);
	ld v3 = cross(p3, p1, p2);
	ld v4 = cross(p4, p1, p2);

	return v1 * v2 < -ERR && v3 * v4 < -ERR;
}

// O(100^3)
void solve(int t) {
	std::cin >> n >> r >> p;
	for (int i = 0; i < n; ++i) std::cin >> hull[i].x >> hull[i].y;
	for (int i = 0; i < r; ++i) std::cin >> routers[i].x >> routers[i].y;
	for (int i = 0; i < p; ++i) std::cin >> points[i].x >> points[i].y;

	std::cout << "Data Set " << t << ":\n";
	for (int i = 0; i < p; ++i) {
		ld strength = 0.0;
		for (int j = 0; j < r; ++j) {
			bool blocked = false;
			for (int k = 0; k < n; ++k) {
				if (intersect(points[i], routers[j], hull[k], hull[(k + 1) % n])) {
					blocked = true;
					break;
				}
			}
			if (!blocked)
				strength = std::max(strength, 1 / distance(points[i], routers[j]));
		}
		std::cout << strength << '\n';
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cout << std::fixed;
	std::cout.precision(2);
	std::cin >> K;
	for (int k = 1; k <= K; ++k) solve(k);
}