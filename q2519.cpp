#include <iostream>

const int LEN = 3001;
typedef long long ll;
struct Pos { ll x, y; } pos[LEN][2];

int N;

ll cross(const Pos& p1, const Pos& p2, const Pos& p3) { 
	return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y; 
}
bool intersect(Pos p1, Pos p2, Pos p3, Pos p4) {
	ll ccw1 = cross(p1, p2, p3), ccw2 = cross(p1, p2, p4);
	ll ccw3 = cross(p3, p4, p1), ccw4 = cross(p3, p4, p2);
	return ccw1 * ccw2 < 0 && ccw3 * ccw4 < 0;
}

bool c[LEN][LEN];

const int MAX = 6001;
inline int get_index(int x, bool b) { return (x - 1) << 1 | b; }
inline int get_neg(int i) { return i ^ 1; }

int main() {
	std::cin >> N;
	for (int n = 0; n < N; ++n) {
		for (int i = 1; i <= 3; ++i) {
			std::cin >> pos[n * 3 + i][0].x >> pos[n * 3 + i][0].y;
			std::cin >> pos[n * 3 + i][1].x >> pos[n * 3 + i][1].y;
		}
		//
	}
	for (int i = 1; i < N * 3; ++i) {
		for (int j = i + 1; j <= N * 3; ++j) {
			if (intersect(pos[i][0], pos[i][1], pos[j][0], pos[j][1]))
				c[i][j] = 1;
		}
	}
	for (int i = 1; i <= N * 3; ++i) {
		for (int j = 1; j <= N * 3; ++j)
			std::cout << c[i][j];
		std::cout << '\n';
	}
}