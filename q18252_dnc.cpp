#include <iostream>
#include <algorithm>
#include <vector>

#include <cassert>

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

struct Tri { 
	int a, b, c;
	Tri& normalize() {
		if (a > b) std::swap(a, b);
		if (b > c) std::swap(b, c);
		if (a > b) std::swap(a, b);
		return *this;
	}
};
ll cross(const std::vector<Pos>& hull, const Tri& t) { return cross(hull[t.a], hull[t.b], hull[t.c]); }

/// <summary>
/// get 2-stable triangle rooted at r
/// </summary>
/// <param name="hull">convex hull</param>
/// <param name="r">root of triangle</param>
/// <returns></returns>
Tri rooted_stable(const std::vector<Pos>& hull, int r) {
	int l = hull.size();
	Tri t = { r, (r + 1) % l, (r + 2) % l };
	for (int j = (r + 2) % l, k = (r + 1) % l; j != r; j = (j + 1) % l) {
		while ((k + 1) % l != j && cross(hull, { r, (k + 1) % l, j }) > cross(hull, { r, k, j })) {
			k = (k + 1) % l;
		}
		if (cross(hull, { r, k, j }) > cross(hull, t)) t = { r, k, j };
	}
	return t.normalize();
}

ll largest_triangle(std::vector<Pos>& hull) {
	int l = hull.size();
	if (l <= 6) { // naive
		ll ret = 0;
		for (int i = 0; i < l; ++i) 
			ret = std::max(ret, cross(hull, rooted_stable(hull, i)));
		return ret;
	}

	Tri t0 = rooted_stable(hull, 0);
	ll ret = cross(hull, t0);

	int m = -1;
	if (!~m && t0.a + 1 < t0.b) m = t0.a + t0.b >> 1;
	if (!~m && t0.b + 1 < t0.c) m = t0.b + t0.c >> 1;
	if (!~m && t0.c + 1 < l - 1) m = t0.c + l >> 1;
	assert(~m);
	Tri tm = rooted_stable(hull, m);
	ret = std::max(ret, cross(hull, tm));
	assert(t0.b <= tm.c);

	if (t0.a < tm.a && tm.a < t0.b &&
		t0.b < tm.b && tm.b < t0.c &&
		t0.c < tm.c && tm.c < l) { // interleave
		std::vector<Pos> p1, p2; // subpolygon
		for (int i = t0.a; i <= tm.a; ++i) p1.push_back(hull[i]);
		for (int i = t0.b; i <= tm.b; ++i) p1.push_back(hull[i]);
		for (int i = t0.c; i <= tm.c; ++i) p1.push_back(hull[i]);
		

		for (int i = tm.a; i <= t0.b; ++i) p2.push_back(hull[i]);
		for (int i = tm.b; i <= t0.c; ++i) p2.push_back(hull[i]);
		for (int i = tm.c; i < l; ++i) p2.push_back(hull[i]);
		p2.push_back(hull[0]);

		std::vector<Pos>().swap(hull); // free memory

		ret = std::max(ret, largest_triangle(p1));
		ret = std::max(ret, largest_triangle(p2));
	}
	else {
		std::vector<Pos> p; // subpolygon
		int arr[7] = { t0.a, t0.b, t0.c, tm.a, tm.b, tm.c };
		std::sort(arr, arr + 6); arr[6] = 0;
		
		// find potential largest subpolygon
		int x = -1;
		for (int i = 0; i < 6; ++i) {
			if ((arr[i] == t0.a && arr[i + 1] == t0.b) ||
				(arr[i] == t0.b && arr[i + 1] == t0.c) ||
				(arr[i] == t0.c && arr[i + 1] == t0.a)) {
				x = i & 1;
				break;
			}
		}
		assert(~x);
		if (!x) {
			for (int i = arr[0]; i <= arr[1]; ++i) p.push_back(hull[i]);
			for (int i = arr[2] + (arr[2] == arr[1]); i <= arr[3]; ++i) p.push_back(hull[i]);
			for (int i = arr[4] + (arr[4] == arr[3]); i <= arr[5]; ++i) p.push_back(hull[i]);
		}
		else {
			for (int i = arr[1]; i <= arr[2]; ++i) p.push_back(hull[i]);
			for (int i = arr[3] + (arr[2] == arr[3]); i <= arr[4]; ++i) p.push_back(hull[i]);
			for (int i = arr[5] + (arr[4] == arr[5]); i < l; ++i) p.push_back(hull[i]);
			if (arr[1]) p.push_back(hull[0]);
		}
		std::vector<Pos>().swap(hull); // free memory

		ret = std::max(ret, largest_triangle(p));
	}

	return ret;
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

	ll ret = largest_triangle(H);
	std::cout << (ret >> 1) << '.' << (ret & 1) * 5;
}