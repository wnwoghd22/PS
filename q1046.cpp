#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

typedef long double ld;
const ld ERR = 1e-10;

char map[50][51];
int N, M;
int light_i, light_j; // 정수 좌표 (zero base, i: row, j: col)
ld light_x, light_y; // 실수 좌표 (x: x축-col, y: y축-row)

struct Vector {
	ld x, y;
};

struct Line {
	Vector v1, v2;
};

struct Slope {
	ld x, y;
	ld radian() const { return atan2(y, x); }
	bool operator<(const Slope& r) const { return radian() < r.radian(); }
};
std::vector<Slope> slopes;
int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }
void push_slopes() {
	// 1 사분면
	for (int i = 0; i <= light_i; ++i) {
		for (int j = 0; j < M - light_j; ++j) {
			// std::cout << i << ' ' << j << '\n';
			int x = j * 2 + 1, y = i * 2 + 1;
			if (gcd(x, y) == 1) {
				slopes.push_back({ (ld)x, (ld)y });
			}
		}
	}
	// 2 사분면
	for (int i = 0; i <= light_i; ++i) {
		for (int j = 0; j <= light_j; ++j) {
			// std::cout << i << ' ' << j << '\n';
			int x = j * 2 + 1, y = i * 2 + 1;
			if (gcd(x, y) == 1) {
				slopes.push_back({ -(ld)x, (ld)y });
			}
		}
	}
	// 3 사분면
	for (int i = 0; i < N - light_i; ++i) {
		for (int j = 0; j <= light_j; ++j) {
			// std::cout << i << ' ' << j << '\n';
			int x = j * 2 + 1, y = i * 2 + 1;
			if (gcd(x, y) == 1) {
				slopes.push_back({ -(ld)x, -(ld)y });
			}
		}
	}
	// 4 사분면
	for (int i = 0; i < N - light_i; ++i) {
		for (int j = 0; j < M - light_j; ++j) {
			// std::cout << i << ' ' << j << '\n';
			int x = j * 2 + 1, y = i * 2 + 1;
			if (gcd(x, y) == 1) {
				slopes.push_back({ (ld)x, -(ld)y });
			}
		}
	}
}

std::vector<Line> edges;
void push_edges() {
	edges.push_back({ {0, 0}, {0, (ld)N} });
	edges.push_back({ {(ld)M, 0}, {(ld)M, (ld)N} });
	edges.push_back({ {0, 0}, {(ld)M, 0} });
	edges.push_back({ {0, (ld)N}, {(ld)M, (ld)N} });

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (map[i][j] == '#') {
				// 빛을 받을 가능성이 있는 쪽만 선분 추가
				Vector ul = { (ld)j, (ld)(N - i) }, ur = { (ld)(j + 1), (ld)(N - i) };
				Vector dl = { (ld)j, (ld)(N - i - 1) }, dr = { (ld)(j + 1), (ld)(N - i - 1) };

				if (i > light_i) edges.push_back({ ul, ur }); // top
				else if (i < light_i) edges.push_back({ dl, dr }); // bottom

				if (j > light_j) edges.push_back({ ul, dl }); // left
				else if (i < light_i) edges.push_back({ ur, dr }); // right
			} 
		}
	}
}

ld ccw() {
	return 0;
}

ld intersect() {
	return 0;
}

std::vector<Line> radial; // 방사형 선분 벡터
void push_radial() { 

}

/*
 * 알고리즘
 * 1. 격자형의 모든 꼭짓점을 향하는 기울기 별 직선을 찾는다.
 * 2. 벽 및 장애물의 표면 직선을 모두 찾는다.
 * 3. 기울기 별 직선에 대해, 왼쪽과 오른쪽으로 각각 교차하는 가장 가까운 점들을 찾는다.
 * 4. 교차점들에 대한 모든 직선들을 각도를 기준으로 정렬한다.
 * 5. 인접한 두 직선이 이루는 모든 삼각형들의 넓이를 구하여 누적한다.
 * 6. 빛이 닿는 면적을 구했으므로, 전체 넓이에서 빼준다.
 */
int main() {
	/*slopes.push_back({ 1, 1 });
	slopes.push_back({ 1, -1 });
	slopes.push_back({ -1, 1 });
	slopes.push_back({ -1, -1 });
	slopes.push_back({ -1, -0.5 });*/
	N = 3, M = 2;
	light_i = 2, light_j = 0;
	push_slopes();
	std::sort(slopes.begin(), slopes.end());

	push_edges();



	for (const Slope& s : slopes) {
		std::cout << s.x << ' ' << s.y << ' ' << s.radian() << '\n';
	}
}