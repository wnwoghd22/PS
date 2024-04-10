#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
typedef long double ld;

const ld ERR = 1e-7;
const ld INF = 1e19;
const int LEN = 1'000'001;

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

std::vector<Line> hull;
int ptr;

void add_line(Line l) {
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
	if (ptr >= hull.size()) ptr = hull.size() - 1;
	return;
}

ll N, A, B, C, x, dp[LEN], S[LEN];
inline ll f(ll x) { return A * x * x + B * x + C; }

int main() {
	std::cin >> N >> A >> B >> C;
	for (int i = 1; i <= N; ++i) {
		std::cin >> x;
		S[i] = S[i - 1] + x;
	}
	for (int n = 1; n <= N; ++n) {
		dp[n] = f(S[n]);
		if (hull.size()) {
			while (ptr < hull.size() - 1 && hull[ptr + 1].x < S[n]) ++ptr;
			int i = hull[ptr].i;
			dp[n] = std::max(dp[n], dp[i] + f(S[n] - S[i]));
		}
		add_line(Line(-2 * A * S[n], A * S[n] * S[n] - B * S[n] + dp[n], -INF, n));
	}
	std::cout << dp[N];
}