#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
typedef long double ld;

const ld ERR = 1e-7;
const ld INF = 1e19;
const int LEN = 100'001;

struct Line {
	ld a, b, x;
	int i;
	Line() {}
	Line(ld a, ld b, ld x, int i) : a(a), b(b), x(x), i(i) {}
	ld operator&(const Line& r) { return (r.b - b) / (a - r.a); } // get pos X of intersect of l and r
};

std::vector<Line> hull;
ll N, a[LEN], b[LEN], dp[LEN];

void add_line(Line l) {
	if (hull.empty()) {
		hull.push_back(l);
		return;
	}
	while (hull.size() > 1 && hull.back().x > (hull.back() & l)) hull.pop_back();
	l.x = hull.back() & l;
	hull.push_back(l);

	/*while (!hull.empty()) {
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
	return;*/
}
int binary_search(int x) {
	int l = 0, r = hull.size() - 1;
	int result = 0, mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (hull[mid].x <= a[x]) {
			result = std::max(result, mid);
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return result;
}
ll f(ll x) {
	int ptr = binary_search(x);
	return hull[ptr].a * a[x] + hull[ptr].b;
}

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> a[i];
	for (int i = 1; i <= N; ++i) std::cin >> b[i];

	add_line(Line(b[1], 0, -INF, 1));
	for (int n = 2; n <= N; ++n) {
		dp[n] = f(n);
		add_line(Line(b[n], dp[n], -INF, n));
	}
	std::cout << dp[N];
}