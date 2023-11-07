#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 300;

struct Pos {
	ll x, y;
	bool operator<(const Pos& r) const { return x == r.x ? y < r.y : x < r.x; }
} p[LEN];

ll cross(const Pos& d1, const Pos& d2, const Pos& d3, const Pos& d4) { return (d2.x - d1.x) * (d4.y - d3.y) - (d2.y - d1.y) * (d4.x - d3.x); }

int N, dp[LEN][LEN], cnt[LEN];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> p[i].x >> p[i].y;
	std::sort(p, p + N);
	for (int i = 0; i < N; ++i)
		for (int j = i + 1; j < N; ++j)
			for (int k = i + 1; k < j; ++k)
				if (cross(p[i], p[j], p[j], p[k]) < 0) dp[i][j]++;

	for (int i = 0; i < N; ++i)
		for (int j = i + 1; j < N; ++j)
			for (int k = i + 1; k < j; ++k)
				if (cross(p[i], p[j], p[j], p[k]) < 0) cnt[dp[i][j] - dp[i][k] - dp[k][j] - 1]++;
				else cnt[dp[i][k] + dp[k][j] - dp[i][j]]++;

	for (int i = 0; i < N - 2; ++i) std::cout << cnt[i] << '\n';

}