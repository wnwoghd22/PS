#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

typedef long long ll;
typedef long double ld;

const ld ERR = 1e-7;
const ll INF = 1e17;
const int LEN = 20'001;

struct Line {
	ll a, b;
	ld x;
	Line() : a(0), b(0), x(-INF) {}
	Line(ll a, ll b, ld x) : a(a), b(b), x(x) {}
	ld operator&(const Line& r) { return (ld)(r.b - b) / (a - r.a); } // get pos X of intersect of l and r
};

std::vector<Line> hull;
ll N, D[LEN], W[LEN];

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
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	ll sum = 0, opt = 0;
	for (int i = 1; i <= N; ++i) {
		std::cin >> W[i] >> D[i];
		sum -= W[i] * D[i - 1];
		W[i] += W[i - 1];
		D[i] += D[i - 1];
	}
	sum += W[N] * D[N];
	add_line(Line(W[1], 0, -INF));
	for (ll i = 2; i <= N; ++i) {
		opt = std::max(opt, f(D[i - 1]) + W[i] * (D[N] - D[i - 1]));
		add_line(Line(W[i], -W[i] * D[i - 1], -INF));
	}
	std::cout << sum - opt;
}