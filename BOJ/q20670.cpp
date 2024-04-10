#include <iostream>
#include <vector>

typedef long long ll;

struct Pos { ll x, y; };
ll cross(const Pos& d1, const Pos& d2, const Pos& d3, const Pos& d4) { return (d2.x - d1.x) * (d4.y - d3.y) - (d2.y - d1.y) * (d4.x - d3.x); }

std::vector<Pos> hull[2];

bool check(const std::vector<Pos>& hull, const Pos& p) {
	int l = 1, r = hull.size() - 1, m;
	while (l < r - 1) {
		m = l + r >> 1;
		ll x = cross(hull[0], hull[m], hull[m], p);
		if (x >= 0) l = m;
		else r = m;
	}
	// std::cout << "pos: " << l << ' ' << r << '\n';
	return cross(hull[0], hull[l], hull[l], p) >= 0 &&
		cross(hull[l], hull[r], hull[r], p) >= 0 &&
		cross(hull[r], hull[0], hull[0], p) >= 0;
}

int N, M, K, ret;

int main() {
	std::cin >> N >> M >> K;
	for (int i = 0, x, y; i < N; ++i) {
		std::cin >> x >> y;
		hull[0].push_back({ x, y });
	}
	for (int i = 0, x, y; i < M; ++i) {
		std::cin >> x >> y;
		hull[1].push_back({ x, y });
	}
	for (int i = 0, x, y; i < K; ++i) {
		std::cin >> x >> y;
		// std::cout << check(hull[0], { x, y }) << ' ';
		/// std::cout << check(hull[1], { x, y }) << '\n';
		if (check(hull[0], { x, y }) && !check(hull[1], { x, y })) ++ret;
	}
	// std::cout << ret << '\n';
	if (ret == K) std::cout << "YES";
	else std::cout << K - ret;
}