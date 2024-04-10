#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
typedef long double ld;

const ld ERR = 1e-7;
const ld INF = 1e17;
const int LEN = 100'001;

struct Line {
	ll a, b;
	ld x;
	int i;
	Line() {}
	Line(ll a, ll b, ld x, int i) : a(a), b(b), x(x), i(i) {}
	ld operator&(const Line& r) { return (ld)(r.b - b) / (a - r.a); } // get pos X of intersect of l and r
	ll f(ll x) { return a * x + b; }
};

std::vector<Line> hull;
ll N, K, a, S[LEN], dp[2][LEN];
int ptr, track[201][LEN];

void add_line(Line l) {
	if (hull.size() && hull.back().a == l.a) {
		hull.back().i = l.i;
		return;
	}
	if (hull.empty()) {
		hull.push_back(l);
		ptr = 0;
		return;
	}
	while (hull.size() > 1 && hull.back().x > (hull.back() & l)) hull.pop_back();
	l.x = hull.back() & l;
	hull.push_back(l);
	if (ptr >= hull.size()) ptr = hull.size() - 1;
}

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> N >> K;
	for (ll i = 1; i <= N; ++i) {
		std::cin >> a;
		S[i] = S[i - 1] + a;
	}
	for (int k = 1; k <= K; ++k) {
		hull.clear();
		add_line(Line(0, 0, -INF, 0));
		for (int n = 1; n <= N; ++n) {
			while (ptr < hull.size() - 1 && hull[ptr + 1].f(S[n]) > hull[ptr].f(S[n])) ++ptr;
			Line l = hull[ptr];
			dp[k & 1][n] = l.f(S[n]);
			track[k][n] = l.i;
			add_line(Line(S[n], dp[k & 1 ^ 1][n] - S[n] * S[n], -INF, n));
		}
	}

	std::cout << dp[K & 1][N] << '\n';
	std::vector<int> result;
	result.push_back(-1);
	for (int i = K, n = N; i >= 1; --i) {
		result.push_back(track[i][n]);
		n = track[i][n];
	}
	std::sort(result.begin(), result.end());
	for (int i = 1; i <= K; ++i) {
		if (!result[i]) result[i] = 1;
		if (result[i] <= result[i - 1]) result[i] = result[i - 1] + 1;
	}
	for (int i = 1; i <= K; ++i) std::cout << result[i] << ' ';
}