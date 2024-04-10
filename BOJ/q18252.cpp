#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const int LEN = 1e4 + 2;

struct Pos {
	ll x, y;
	bool operator<(const Pos& p) const { return x == p.x ? y < p.y : x < p.x; }
	friend std::istream& operator>>(std::istream& is, Pos& p) { is >> p.x >> p.y; return is; }
} p[LEN];
ll cross(const Pos& p1, const Pos& p2, const Pos& p3) { return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x); }
ll dot(const Pos& p1, const Pos& p2, const Pos& p3) { return (p2.x - p1.x) * (p3.x - p2.x) + (p2.y - p1.y) * (p3.y - p2.y); }

void monotone_chain(std::vector<Pos>& p, std::vector<Pos>& hull) {
	std::sort(p.begin(), p.end());
	if (p.size() <= 2) {
		for (const Pos& pos : p) hull.push_back(pos);
		return;
	}
	for (int i = 0; i < p.size(); ++i) {
		while (hull.size() > 1 && cross(hull[hull.size() - 2], hull[hull.size() - 1], p[i]) <= 0) hull.pop_back();
		hull.push_back(p[i]);
	}
	hull.pop_back();
	int s = hull.size() + 1;
	for (int i = p.size() - 1; i >= 0; --i) {
		while (hull.size() > s && cross(hull[hull.size() - 2], hull[hull.size() - 1], p[i]) <= 0) hull.pop_back();
		hull.push_back(p[i]);
	}
	hull.pop_back();
}

int N, M;
std::vector<Pos> P, H;
Pos U, D;

int main() {
	std::cin >> N >> U >> D;
	P.push_back(U); P.push_back(D);
	for (int i = 0, y, xs, xe; i < N; ++i) {
		std::cin >> y >> xs >> xe;
		if (cross(U, D, { xs, y }) > 0) P.push_back({ xs, y });
		if (cross(U, D, { xe, y }) < 0) P.push_back({ xe, y });
	}
	monotone_chain(P, H);
	M = H.size();
	if (M < 3) {
		std::cout << 0;
		return 0;
	}

	ll ret = 0;
	for (int i = 0; i < M; ++i) {
		for (int j = (i + 2) % M, k = (i + 1) % M; j != i; j = (j + 1) % M) {
			while ((k + 1) % M != j && cross(H[i], H[(k + 1) % M], H[j]) > cross(H[i], H[k], H[j])) {
				k = (k + 1) % M;
			}
			ret = std::max(ret, cross(H[i], H[k], H[j]));
		}
	}
	std::cout << (ret >> 1) << '.' << (ret & 1) * 5;
}