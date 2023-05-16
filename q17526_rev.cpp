#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

typedef long long ll;
typedef long double ld;

const ld ERR = 1e-7;
const ll INF = 1e17;
const int LEN = 100'001;

struct Line {
	ll a, b;
	ld x;
	Line() : a(0), b(0), x(-INF) {}
	Line(ll a, ll b, ld x) : a(a), b(b), x(x) {}
	ld operator&(const Line& r) { return (ld)(r.b - b) / (a - r.a); } // get pos X of intersect of l and r
};

std::vector<Line> hull;
ll N, dist[LEN], S[LEN], P[LEN], dp[LEN];

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
	int l = 0, r = hull.size() - 1, m;
	while (l < r) {
		m = l + r + 1 >> 1;
		if (hull[m].x < x) l = m;
		else r = m - 1;
	}
	return l;
}
ll f(ll x) {
	int ptr = binary_search(x);
	return hull[ptr].a * x + hull[ptr].b;
}

int main() {
	std::cin >> N;
	for (int i = 1; i < N; ++i) std::cin >> dist[i];
	for (int i = 1; i < N; ++i) std::cin >> P[i] >> S[i];

	add_line(Line());
	for (ll i = N - 1, d = 0; i >= 1; --i) {
		d += dist[i];
		dp[i] = f(S[i]) + d * S[i] + P[i];
		add_line(Line(-d, dp[i], -INF));
	}
	for (int i = 1; i < N; ++i) std::cout << dp[i] << ' ';
	std::cout << dp[1];
}