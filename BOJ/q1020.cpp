#include <iostream>

typedef long long int ll;
const ll INF = 1e17;
ll N, result, CYCLE, dp[17][150];
int v[] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 5 };
std::string S;

int main() {
	std::cin >> S;
	for (const char& c : S) N = N * 10 + c - '0';

	for (int i = 0; i < 17; ++i)
		for (int j = 0; j < 150; ++j)
			dp[i][j] = INF;
	for (ll i = 0; i < 10; ++i) dp[1][v[i]] = std::min(dp[1][v[i]], i);
	for (ll n = 2; n <= S.length(); ++n) {
		ll l = (n - 1) * 2, r = (n - 1) * 7;
		for (ll i = 2; i < 8; ++i) {
			for (ll j = l; j <= r; ++j) {
				dp[n][i + j] = std::min(dp[n][i + j], dp[1][i] * (ll)pow(10, n - 1) + dp[n - 1][j]);
			}
		}
	}

	result = CYCLE = pow(10, S.length());

	// first digit
	ll c, d = N % 10;
	for (ll i = 0; i < 10; ++i) {
		if (i ^ d && v[i] == v[d]) {
			if (i > d) result = std::min(result, i - d);
			else result = std::min(result, CYCLE + i - d);
		}
	}
	// others
	c = v[N % 10], d = N / 10;
	for (ll i = 2, e = 10; i <= S.length(); ++i, e *= 10) {
		c += v[d % 10]; d /= 10;
		ll n = N % (e * 10);
		for (ll j = 0; j <= 9; ++j) {
			if (c - v[j] >= 0) {
				ll min_num = dp[i - 1][c - v[j]];
				ll next = j * e + min_num;
				if (n ^ next && min_num < INF) {
					if (next > n) result = std::min(result, next - n);
					else result = std::min(result, CYCLE + next - n);
				}
			}
		}
	}
	std::cout << result;
}