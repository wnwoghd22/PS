#include <iostream>

struct Pos {
	int x, y;
} p[3000];

int distance(const Pos& l, const Pos& r) { return (l.x - r.x) * (l.x - r.x) + (l.y - r.y) * (l.y - r.y); }

int main() {
	int N, max, min = 1e9, min_i;
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> p[i].x >> p[i].y;
	for (int i = 0; i < N; ++i) {
		max = 0;
		for (int j = 0; j < N; ++j) {
			if (i == j) continue;
			int dist = distance(p[i], p[j]);
			if (dist > max) max = dist;
		}
		if (max < min) min = max, min_i = i;
	}
	std::cout << p[min_i].x << ' ' << p[min_i].y;
}