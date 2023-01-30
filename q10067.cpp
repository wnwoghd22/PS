#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
typedef long double ld;

const ld ERR = 1e-7;
const ld INF = 1e19;
const int LEN = 100'001;

struct Line {
	ld a, b, x, y;
	Line() {}
	Line(ld a, ld b, ld x, ld y) : a(a), b(b), x(x), y(y) {}
	ld operator&(const Line& r) { return (r.b - b) / (a - r.a); } // get pos X of intersect of l and r
};

std::vector<Line> hull;
ll N, K, a, S[LEN], dp[201][LEN];
int ptr, track[201][LEN];

void add_line(Line l) {
	if (hull.size() && abs(hull.back().a - l.a) < ERR) {
		hull.back().y = l.y;
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
	std::cin >> N >> K;
	for (ll i = 1, p = 1; i <= N; ++i) {
		std::cin >> a;
		S[i] = S[i - 1] + a;
	}
	for (int k = 1; k <= K; ++k) {
		hull.clear();
		add_line(Line(0, 0, 0, 0));
		for (int n = 1; n <= N; ++n) {
			while (ptr < hull.size() - 1 && hull[ptr + 1].x < S[n]) ++ptr;
			Line l = hull[ptr];
			dp[k][n] = l.a * S[n] + l.b;
			track[k][n] = l.y;
			add_line(Line(S[n], dp[k - 1][n] - S[n] * S[n], -INF, n));
		}
	}

	std::cout << dp[K][N] << '\n';
	std::vector<int> result;
	int now = N;
	result.push_back(-1);
	for (int i = K; i >= 1; --i) {
		result.push_back(track[i][now]);
		now = track[i][now];
	}
	std::sort(result.begin(), result.end());
	for (int i = 1; i <= K; ++i) {
		if (!result[i]) result[i] = 1;
		if (result[i] <= result[i - 1]) result[i] = result[i - 1] + 1;
	}
	for (int i = 1; i <= K; i++) std::cout << result[i] << ' ';

}