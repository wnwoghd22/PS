#include <iostream>

const int LEN = 1000;

int N;
struct Pos { int x, y; } p[LEN];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> p[i].x >> p[i].y;
	for (int i = 0; i < N; ++i) {
		int v = 0;
		int dist = 0;
		for (int j = 0; j < N; ++j) {
			int dx = p[j].x - p[i].x;
			int dy = p[j].y - p[i].y;
			int d = dx * dx + dy * dy;
			if (d > dist) {
				dist = d;
				v = j + 1;
			}
		}
		std::cout << v << '\n';
	}
}