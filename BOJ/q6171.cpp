#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
typedef long double ld;

const ld ERR = 1e-7;
const ld INF = 1e19;
const int LEN = 50'001;

struct Land {
	ll w, h;
	bool operator<(const Land& r) { return w == r.w ? h > r.h : w < r.w; }
} lands[LEN];
struct Line {
	ld a, b, x;
	int i;
	Line() {}
	Line(ld a, ld b, ld x, int i) : a(a), b(b), x(x), i(i) {}
	ld operator&(const Line& r) { return (r.b - b) / (a - r.a); } // get pos X of intersect of l and r
};

std::vector<Land> target;
std::vector<Line> hull;
ll N, dp[LEN];

void add_line(Line l) {
	if (hull.empty()) {
		hull.push_back(l);
		return;
	}
	while (hull.size() > 1 && hull.back().x > (hull.back() & l)) hull.pop_back();
	l.x = hull.back() & l;
	hull.push_back(l);
}
int binary_search(int x) {
	for (const Line& l : hull)
		std::cout << l.a << ' ' << l.b << ' ' << l.x << '\n';

	int l = 0, r = hull.size() - 1;
	int result = 0, mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (hull[mid].x <= x) {
			if (abs(hull[mid].x - hull[result].x) < ERR) {
				result = std::min(result, mid);
			}
			else result = std::max(result, mid);
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return result;
}
ll f(ll x) {
	int ptr = binary_search(target[x].w);
	std::cout << "ptr: " << hull[ptr].a << ' ' << hull[ptr].b << '\n';
	return hull[ptr].a * target[x].w + hull[ptr].b;
}

int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> lands[i].w >> lands[i].h;
	std::sort(lands, lands + N);

	for (int i = 0; i < N; ++i)
		std::cout << lands[i].w << ' ' << lands[i].h << '\n';

	int width = 0;
	for (int i = 0; i < N; ++i) { // make monotonic
		if (lands[i].w == width) continue;
		width = lands[i].w;
		while (target.size() && target.back().h <= lands[i].h) target.pop_back();
		target.push_back(lands[i]);
	}
	for (const Land& l : target)
		std::cout << l.w << ' ' << l.h << '\n';
	
	int L = target.size();
	dp[0] = target[0].h * target[0].w;
	add_line(Line(target[0].h, 0, -INF, 1));
	for (int n = 1; n < L; ++n) {
		add_line(Line(target[n].h, dp[n - 1], -INF, n));
		dp[n] = f(n);
	}
	std::cout << dp[L - 1];
}