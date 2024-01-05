#include <iostream>
#include <algorithm>

const int LEN = 100'000;

int N, ret;
struct Pos {
	int x, y;
	bool operator<(const Pos& r) const { return x == r.x ? y < r.y : x < r.x; }
} p[LEN];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> p[i].x >> p[i].y;
	std::sort(p, p + N);
	for (int i = 0; i < N; i += 2) ret += p[i + 1].y - p[i].y;
	
	for (int i = 0; i < N; ++i) std::swap(p[i].x, p[i].y);
	std::sort(p, p + N);
	for (int i = 0; i < N; i += 2) ret += p[i + 1].y - p[i].y;

	std::cout << ret;
}