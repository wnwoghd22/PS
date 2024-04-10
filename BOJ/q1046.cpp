#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

typedef long double ld;
const ld ERR = 1e-7;

char map[50][51];
int N, M;
int light_i, light_j; // 정수 좌표 (zero base, i: row, j: col)
ld light_x, light_y; // 실수 좌표 (x: x축-col, y: y축-row)

struct Vector {
	ld x, y;
	Vector() : x(0), y(0) {}
	Vector(ld x, ld y) : x(x), y(y) {}
	Vector operator*(ld scalar) const {
		Vector result(*this);
		result.x *= scalar;
		result.y *= scalar;
		return result;
	}
	ld magnitude() const { return sqrt(x * x + y * y); }
	Vector normalize() const {
		Vector result(*this);
		return result * (1 / magnitude());
	}
	Vector operator+(const Vector& r) const { return Vector(x + r.x, y + r.y); }
	Vector operator-(const Vector& r) const { return Vector(x - r.x, y - r.y); }
	ld radian() const { return atan2(y, x); }
	bool operator<(const Vector& r) const { return radian() < r.radian(); }
};

struct Line {
	Vector v1, v2;
};
std::vector<Vector> slopes;
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

	std::sort(slopes.begin(), slopes.end());
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
				else if (j < light_j) edges.push_back({ ur, dr }); // right
			} 
		}
	}
}

// cross product
ld cross(const Vector& p1, const Vector& p2, const Vector& p3) { return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y; }

/// <summary>
/// 직선 a는 광원으로부터 뻗어나오는 논리적 무한대 길이의 직선이므로 추가적인 판정 로직은 필요 없음
/// 직선 a와 선분 b는 절대 평행하지 않음
/// </summary>
/// <param name="a">광원으로부터 뻗어나오는 반직선. 광원 위치는 v1</param>
/// <param name="b"></param>
/// <returns></returns>
int intersect(const Line& a, const Line& b) {
	Vector p1 = a.v1, p2 = a.v2, p3 = b.v1, p4 = b.v2;
	ld ccw1 = cross(p1, p2, p3), ccw2 = cross(p1, p2, p4);
	ld ccw3 = cross(p3, p4, p1), ccw4 = cross(p3, p4, p2);
	if (ccw1 * ccw2 < -ERR && ccw3 * ccw4 < -ERR) { // restrict intersect. 완전 교차
		return 1;
	}
	if (std::abs(ccw1 * ccw2) < ERR && ccw3 * ccw4 < -ERR) { // p3 또는 p4가 직선 위에 있음
		if (std::abs(ccw1) < ERR) { // p3이 직선 위에 있다면 p4가 왼쪽 또는 오른쪽에 있는지 판정
			if (ccw2 > 0) { // 왼쪽 (반시계)
				return 2;
			}
			else return 3; // 오른쪽 (시계)
		}
		if (std::abs(ccw2) < ERR) { // p4가 직선 위에 있다면 p3이 왼쪽 또는 오른쪽에 있는지 판정
			if (ccw1 > 0) { // 왼쪽 (반시계)
				return 2;
			}
			else return 3; // 오른쪽 (시계)
		}
	}
	return 0;
}
Vector intersection_point(const Line& a, const Line& b) {
	Vector p1 = a.v1, p2 = a.v2, p3 = b.v1, p4 = b.v2;
	Vector ret;
	ret.x = ((p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) - (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x)) / ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));
	ret.y = ((p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x)) / ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));
	return ret;
}

std::vector<Line> radial; // 방사형 선분 벡터
void push_radial() { 
	Vector p1 = { light_x, light_y };
	for (const Vector& s : slopes) {
		// std::cout << "Slope: " << s.x << ' ' << s.y;
		Vector p2 = p1 + s.normalize() * 100;
		Line a = { p1, p2 }; // 광원 p1로부터 뻗어나가는 반직선
		ld l_len = 100, r_len = 100;
		for (const Line& b : edges) {
			int cur = intersect(a, b);
			bool l = 0, r = 0;
			if (cur == 1) { // 왼쪽, 오른쪽 방사형 선분 길이 업데이트
				// std::cout << "case 1: " << b.v1.x << ' ' << b.v1.y << ' ' << b.v2.x << ' ' << b.v2.y << '\n';
				l = r = 1;
			}
			else if (cur == 2) l = 1; // 왼쪽 방사형 선분 길이 업데이트
			else if (cur == 3) r = 1; // 오른쪽 방사형 선분 길이 업데이트

			if (l) l_len = std::min(l_len, (intersection_point(a, b) - p1).magnitude());
			if (r) r_len = std::min(r_len, (intersection_point(a, b) - p1).magnitude());
		}
		Vector vl = p1 + s.normalize() * l_len;
		Vector vr = p1 + s.normalize() * r_len;
		// std::cout << "Vector R: " << vr.x << ' ' << vr.y << " Vector L: " << vl.x << ' ' << vl.y << '\n';
		radial.push_back({ p1, p1 + s.normalize() * r_len });
		radial.push_back({ p1, p1 + s.normalize() * l_len });
	}
}

ld get_light_area() {
	ld area = 0;
	for (int i = 1; i < radial.size(); i += 2) {
		// std::cout << "triangle: " << radial[i].v2.x << ' ' << radial[i].v2.y << " -> " << radial[(i + 1) % radial.size()].v2.x << ' ' << radial[(i + 1) % radial.size()].v2.y << '\n';
		area += std::abs(cross(radial[i].v1, radial[i].v2, radial[(i + 1) % radial.size()].v2));
	}
	return area / 2;
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
	freopen("input.txt", "r", stdin);
	std::cout << std::fixed;
	std::cout.precision(10);
	
	ld wall_area = 0;
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		std::cin >> map[i];
		for (int j = 0; j < M; ++j) {
			if (map[i][j] == '*') { // light point
				light_i = i, light_j = j;
				light_x = j + 0.5, light_y = N - i - 0.5;
			}
			if (map[i][j] == '#') wall_area += 1;
		}
	}

	push_slopes();

	push_edges();

	push_radial();

	ld light_area = get_light_area();

	/*std::cout << "map:\n";
	for (int i = 0; i < N; ++i)
		std::cout << map[i] << '\n';

	std::cout << "slope counts: " << slopes.size() << '\n';
	std::cout << "edge counts: " << edges.size() << '\n';
	std::cout << "light pos: (" << light_x << ", " << light_y << ")\n";
	std::cout << "light area: " << light_area << '\n';
	std::cout << "wall area: " << wall_area << '\n';*/

	std::cout << N * M - light_area - wall_area;
}