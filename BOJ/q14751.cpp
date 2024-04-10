#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
typedef long double ld;

const ld ERR = 1e-15;

struct Line {
	ld a, b, x;
	int i;
	Line() {}
	Line(ld a, ld b, ld x, int i) : a(a), b(b), x(x), i(i) {}
	bool operator<(const Line& r) {
		if (abs(a - r.a) < ERR) return b < r.b;
		return a > r.a;
	}
	ld operator&(const Line& r) { return (r.b - b) / (a - r.a); } // get pos X of intersect of l and r
};

ld minX, maxX;
int N, M;

std::vector<Line> lines;
std::vector<std::pair<ld, int>> queries;
std::vector<Line> hull;
int ptr;

void add_line(Line& l) {
	if (hull.empty()) {
		hull.push_back(l);
		return;
	}
	while (!hull.empty()) {
		Line top = hull.back();
		if (abs(top.a - l.a) < ERR && top.b < l.b) return;
		if (abs(top.a - l.a) < ERR) hull.pop_back();
		else {
			ld x = top & l;
			if (x <= top.x) hull.pop_back();
			else break;
		}
	}
	if (hull.empty()) hull.push_back(l);
	else {
		l.x = hull.back() & l;
		hull.push_back(l);
	}
	// if (ptr >= hull.size()) ptr = hull.size() - 1;
	return;
}

int query(ld x) {
	while (ptr < hull.size() - 1 && hull[ptr + 1].x < x) ++ptr;
	return hull[ptr].i;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> maxX >> minX >> N;
	ld dx = maxX - minX;
	for (int i = 1; i <= N; ++i) {
		ld upY, lowY;
		std::cin >> upY >> lowY;
		ld dy = upY - lowY;
		ld a = dy / dx;
		ld b = lowY - a * minX;
		lines.push_back(Line(a, b, minX, i));
	}
	std::cin >> M;
	for (int i = 0; i < M; ++i) {
		ld x;
		std::cin >> x;
		queries.push_back({ x, i });
	}
	std::sort(lines.begin(), lines.end());
	std::sort(queries.begin(), queries.end());
	std::vector<int> ans(M);
	for (Line& l : lines) add_line(l);
	for (const auto& q : queries) ans[q.second] = query(q.first);
	for (const int& i : ans) std::cout << i << '\n';
}