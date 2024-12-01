#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 3000;

int N;

struct Pos {
	int x, y;
	bool operator<(const Pos& o) const { return x == o.x ? y < o.y : x < o.x; }
} p[LEN];

struct Vec {
	int x, y;
	bool operator<(const Vec& o) const { return x * o.y < o.x * y; }
} v[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	ll ret = 0;
	for (int i = 0; i < N; ++i) std::cin >> p[i].x >> p[i].y;
	std::sort(p, p + N);
	for (int i = 2; i < N; ++i) {
		for (int j = 0; j < i; ++j)
			v[j] = { p[i].x - p[j].x, p[i].y - p[j].y };
		std::sort(v, v + i);
		ll sx = 0, sy = 0;
		for (int j = 0; j < i; ++j) {
			ret -= sx * v[j].y - v[j].x * sy;
			sx += v[j].x; sy += v[j].y;
		}
	}
	std::cout << ret / 2 << '.' << (ret & 1) * 5;
}