#include <iostream>
#include <algorithm> // for shuffle
#include <random>
#include <vector>

const double INF = 1e18;
const double ERR = 1e-7;

struct Pos { double x, y; };
double distance(const Pos& a, const Pos& b) { 
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
Pos get_center(const Pos& a, const Pos& b) {
	return { (a.x + b.x) / 2, (a.y + b.y) / 2 };
}
Pos get_center(const Pos& a, const Pos& b, const Pos& c) {
	double bx = b.x - a.x, by = b.y - a.y;
	double cx = c.x - a.x, cy = c.y - a.y;
	double B = bx * bx + by * by;
	double C = cx * cx + cy * cy;
	double D = bx * cy - by * cx;
	return { (cy * B - by * C) / (2 * D) + a.x,(bx * C - cx * B) / (2 * D) + a.y };
}

struct Circle {
	Pos c;
	double r;
	bool is_inside(const Pos& p) {
		return distance(c, p) < r + ERR;
	}
	bool is_valid(const std::vector<Pos>& v) {
		for (const Pos& p : v)
			if (!is_inside(p))
				return false;
		return true;
	}
};
Circle get_circle(const Pos& a, const Pos& b) {
	return { get_center(a, b), distance(a, b) / 2 };
}
Circle get_circle(const Pos& a, const Pos& b, const Pos& c) {
	Pos center = get_center(a, b, c);
	return { center, distance(a, center) };
}

Circle get_min_circle(std::vector<Pos>& p) {
	if (p.empty()) return { {0, 0}, 0 };
	if (p.size() == 1) return { p[0], 0 };
	if (p.size() == 2) return get_circle(p[0], p[1]);
	for (int i = 0; i < p.size() - 1; ++i) {
		for (int j = i + 1; j < p.size(); ++j) {
			Circle c = get_circle(p[i], p[j]);
			if (c.is_valid(p))
				return c;
		}
	}
	return get_circle(p[0], p[1], p[2]);
}

Circle welzl(std::vector<Pos>& p, std::vector<Pos> r, int n) {
	if (n == 0 || r.size() == 3) { return get_min_circle(r); }

	int i = rand() % n;
	Pos cur = p[i];

	std::swap(p[i], p[n - 1]); // remove p[i]

	Circle mec = welzl(p, r, n - 1); // get mec from set P - {p[i]}

	if (mec.is_inside(cur)) return mec;

	r.push_back(cur);
	return welzl(p, r, n - 1);
}

int N;
std::vector<Pos> P, R;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		double x, y;
		std::cin >> x >> y;
		P.push_back({ x, y });
	}
	std::mt19937 g(1);
	std::shuffle(P.begin(), P.end(), g);

	Circle mec = welzl(P, R, N);

	std::cout.precision(7);
	std::cout << std::fixed;
	std::cout << mec.c.x << ' ' << mec.c.y << ' ' << mec.r;
}