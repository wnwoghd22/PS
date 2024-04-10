#include <iostream>
#include <algorithm>

typedef long long ll;
typedef long double ld;
const int LEN = 100;
const int INF = 1e9;
const ld ERR = 1e-9;

struct Pos { ll x, y; } pos1[LEN], pos2[LEN];
ll cross(const Pos& p1, const Pos& p2, const Pos& p3) {
	return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
}
bool is_inside(const Pos& p, const Pos* h, int n) {
	for (int i = 0; i < n; ++i)
		if (cross(h[i], h[(i + 1) % n], p) <= 0)
			return false;
	return true;
}
bool is_intersect(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) {
	ll ccw1 = cross(p1, p2, p3), ccw2 = cross(p1, p2, p4);
	ll ccw3 = cross(p3, p4, p1), ccw4 = cross(p3, p4, p2);
	return ccw1 * ccw2 < 0 && ccw3 * ccw4 < 0;
}

bool in1[LEN], in2[LEN];

struct P {
	ld x, y;
	bool operator<(const P& r) const {
		return abs(x - r.x) < ERR ? y < r.y : x < r.x;
	}
} p[LEN], hull1[LEN * 3], hull2[LEN * 3];
ld cross(const P& p1, const P& p2, const P& p3) {
	return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
}

P intersection(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) {
	P ret;

	ret.x = ((p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) - (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x)) / 
		(ld)((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));
	ret.y = ((p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x)) / 
		(ld)((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));

	return ret;
}

int N, M;

int len, sp1, sp2;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;

	for (int i = 0; i < N; ++i) std::cin >> pos1[i].x >> pos1[i].y;
	for (int j = 0; j < M; ++j) std::cin >> pos2[j].x >> pos2[j].y;

	for (int i = 0; i < N; ++i) {
		if (is_inside(pos1[i], pos2, M))
			in1[i] = 1;
	}
	for (int j = 0; j < M; ++j) {
		if (is_inside(pos2[j], pos1, N))
			in2[j] = 1;
	}
	// for (int i = 0; i < N; ++i) std::cout << in1[i] << ' '; std::cout << '\n';
	// for (int j = 0; j < M; ++j) std::cout << in2[j] << ' '; std::cout << '\n';

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			if (is_intersect(pos1[i], pos1[(i + 1) % N], pos2[j], pos2[(j + 1) % M]))
				p[len++] = intersection(pos1[i], pos1[(i + 1) % N], pos2[j], pos2[(j + 1) % M]);
		
	for (int i = 0; i < N; ++i) if (in1[i] == 1) p[len++] = { (ld)pos1[i].x, (ld)pos1[i].y };
	for (int j = 0; j < M; ++j) if (in2[j] == 1) p[len++] = { (ld)pos2[j].x, (ld)pos2[j].y };

	std::sort(p, p + len);

	 std::cout << "hull\n";
	 for (int i = 0; i < len; ++i) {
	 	std::cout << p[i].x << ' ' << p[i].y << '\n';
	 }

	hull1[sp1++] = p[0];
	hull1[sp1++] = p[1];

	for (int i = 2; i < len; ++i) {
		while (sp1 > 1) {
			if (cross(hull1[sp1 - 2], hull1[sp1 - 1], p[i]) < 0) --sp1;
			else break;
		}
		hull1[sp1++] = p[i];
	}

	hull2[sp2++] = p[len - 1];
	hull2[sp2++] = p[len - 2];

	for (int i = len - 3; i >= 0; --i) {
		while (sp2 > 1) {
			if (cross(hull2[sp2 - 2], hull2[sp2 - 1], p[i]) < 0) --sp2;
			else break;
		}
		hull2[sp2++] = p[i];
	}

	ld area = 0;

	for (int i = 0; i < sp1; ++i) area += cross(hull1[i], hull1[(i + 1) % sp1], { 0, 0 });
	for (int i = 0; i < sp2; ++i) area += cross(hull2[i], hull2[(i + 1) % sp2], { 0, 0 });

	std::cout << std::fixed;
	std::cout.precision(10);
	std::cout << area / 2;
}