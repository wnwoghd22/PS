#include <iostream>
#include <algorithm>

typedef long long ll;
ll N, A[2][3], dp[2][2][3];
ll m(ll x, ll y) { return x < y ? x : y; }
ll M(ll x, ll y) { return x > y ? x : y; }
ll f(int i, ll x, ll y) { return i ? m(x, y) : M(x, y); }

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	std::cin >> A[0][0] >> A[0][1] >> A[0][2];
	dp[0][0][1] = dp[1][0][1] = std::abs(A[0][0] - A[0][1]);
	dp[0][0][2] = dp[1][0][2] = std::abs(A[0][2] - A[0][1]);

	for (int i = 1, v[3], h[3]; i < N; ++i) {
		std::cin >> A[i & 1][0] >> A[i & 1][1] >> A[i & 1][2];
		for (int j = 0; j < 3; ++j) v[j] = std::abs(A[0][j] - A[1][j]);
		h[1] = std::abs(A[i & 1][0] - A[i & 1][1]);
		h[2] = std::abs(A[i & 1][2] - A[i & 1][1]);

		if (i & 1) {
			for (int j = 0; j < 2; ++j) {
				dp[j][1][0] = f(j, dp[j][0][0] + v[0] + v[1] + v[2], 
					f(j, dp[j][0][1] + h[1] + v[2], dp[j][0][2] + h[2] + v[0]));
				dp[j][1][1] = dp[j][0][2] + v[0];
				dp[j][1][2] = dp[j][0][1] + v[2];
			}
		}
		else {
			for (int j = 0; j < 2; ++j) {
				dp[j][0][0] = f(j, dp[j][1][0], f(j, dp[j][1][2] + h[1], dp[j][1][1] + h[2]));
				dp[j][0][1] = f(j, dp[j][1][0] + h[1], dp[j][1][2] + v[0] + v[1]);
				dp[j][0][2] = f(j, dp[j][1][0] + h[2], dp[j][1][1] + v[2] + v[1]);
			}
		}
	}
	std::cout << dp[0][1][0] << '\n' << dp[1][1][0];
}