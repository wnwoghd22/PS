#include <stdio.h>
#define ll long long
#define LEN 2000
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

int N, y[LEN], dp[LEN][LEN]; // dp(l -> r): maximum possible count from l to r

int solve() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) scanf("%d", y + i);
	dp[0][0] = 1;
	for (int r = 1; r < N; ++r) {
		dp[r][r] = 1;
		ll p = r, S = 1;
		for (int l = r - 1; l >= 0; --l) {
			if ((y[p] - y[l]) * (r - p) <= (y[r] - y[p]) * (p - l)) { // visible
				S += dp[l + 1][p - 1];
				dp[l][r] = MAX(dp[l][r - 1], S);
				p = l;
			}
			else dp[l][r] = MAX(dp[l][r - 1], S + dp[l][p - 1]);
		}
	}
	return dp[0][N - 1];
}

int main() {
	int t, T;
	scanf("%d", &T);
	for (t = 1; t <= T; ++t)
		printf("#%d %d\n", t, solve());
}