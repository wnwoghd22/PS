#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>

typedef long double ld;
const int LEN = 200'001;
const ld TOL = 1e-9, INF = 2e20;
int N, M, Q, q;

bool z(ld x) { return std::abs(x) < TOL; }
struct Pos {
	ld x, y;
	bool operator<(const Pos& p) const { return z(x - p.x) ? y < p.y : x < p.x; }
} U, D, X, Y, P;
std::vector<Pos> pos, buffer, u, d;

ld cross(const Pos& d1, const Pos& d2, const Pos& d3) {
	return (d2.x - d1.x) * (d3.y - d2.y) - (d2.y - d1.y) * (d3.x - d2.x);
}
ld dot(const Pos& d1, const Pos& d2, const Pos& d3) {
	return (d2.x - d1.x) * (d3.x - d2.x) + (d2.y - d1.y) * (d3.y - d2.y);
}
int ccw(const Pos& d1, const Pos& d2, const Pos& d3) {
	ld c = cross(d1, d2, d3);
	return c > TOL ? 1 : c < -TOL ? -1 : 0;
}
std::vector<Pos> lower_hull(std::vector<Pos>& C) {  //lower monotone chain
	std::vector<Pos> H;
	//std::sort(C.begin(), C.end());
	if (C.size() <= 2) {
		for (const Pos& pos : C) H.push_back(pos);
		return H;
	}
	for (int i = 0; i < C.size(); i++) {
		while (H.size() > 1 && cross(H[H.size() - 2], H[H.size() - 1], C[i]) < TOL) {
			H.pop_back();
		}
		H.push_back(C[i]);
	}
	return H;
}
std::vector<Pos> upper_hull(std::vector<Pos>& C) {  //upper monotone_chain
	std::vector<Pos> H;
	//std::sort(C.begin(), C.end());
	if (C.size() <= 2) {
		for (int i = C.size() - 1; i >= 0; i--) H.push_back(C[i]);
		return H;
	}
	for (int i = C.size() - 1; i >= 0; i--) {
		while (H.size() > 1 && cross(H[H.size() - 2], H[H.size() - 1], C[i]) < TOL) {
			H.pop_back();
		}
		H.push_back(C[i]);
	}
	return H;
}

Pos ternary_search(std::vector<Pos>& H, const Pos& p1, const Pos& p2) {
	int s = 0, e = H.size() - 1, l, r;
	ld min = INF;
	Pos ret = H[0];
	while (e - s > 2) {
		l = (s + s + e) / 3;
		r = (s + e + e) / 3;
		ld cl = cross(p1, p2, H[l]), cr = cross(p1, p2, H[r]);
		if (cl > cr) s = l;
		else e = r;
	}
	for (int i = s; i <= e; ++i) {
		if (cross(p1, p2, H[i]) < min) {
			min = cross(p1, p2, H[i]);
			ret = H[i];
		}
	}
	return ret;
}
bool intersect(const Pos& x, const Pos& y, const Pos& u, const Pos& d) {
	return ccw(x, y, u) * ccw(x, y, d) <= 0;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	std::cin >> N >> Q;
	pos.resize(N);
	for (int i = 0; i < N; i++) std::cin >> pos[i].x >> pos[i].y;
	std::sort(pos.begin(), pos.end());
	d = lower_hull(pos), u = upper_hull(pos);
	while (Q--) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> P.x >> P.y;
			buffer.push_back(P);
			if (buffer.size() >= 300) {
				for (const Pos& p : buffer) pos.push_back(p);
				std::sort(pos.begin(), pos.end());
				d = lower_hull(pos), u = upper_hull(pos);
				buffer.clear();
			}
		}
		else if (q == 2) {
			bool flag = 0;
			ld A, B, C;
			std::cin >> A >> B >> C;
			if (z(A)) {
				X = { 0, C / B };
				Y = { 1, C / B };
			}
			else if (z(B)) {
				X = { C / A, 0 };
				Y = { C / A, 1 };
			}
			else { 
				X = { 0, C / B }; 
				Y = { C / A, 0 };
			}
			if (Y < X) std::swap(Y, X);
			D = ternary_search(d, X, Y);
			U = ternary_search(u, Y, X);
			if (!intersect(X, Y, U, D)) {
				int side = ccw(X, Y, U);
				for (const Pos& p : buffer) {
					int cur = ccw(X, Y, p);
					if (cur != side) {
						flag = 1;
						break;
					}
				}
			}
			else flag = 1;
			
			std::cout << (flag ? "NO\n" : "YES\n");
		}
	}
}