#include <iostream>

typedef long long ll;
ll MAX = 9876543210ll;
int dp[11][11], c10[11];

int d[11];
int f(ll k) {
	int l = 0, result = 0;
	do d[l++] = k % 10; while (k /= 10);
	for (int i = l - 1; i >= 0; --i) {
		if (!i) result += d[0] + 1;
		else {
			if (d[i] > d[i - 1]) result += dp[d[i]][i + 1];
			else {
				result += dp[d[i] + 1][i + 1];
				break;
			}
		}
	}
	result += c10[l - 1];
	return result - 1;
}
ll binary_search(int n) {
	ll l = 0, r = MAX, m, result = MAX + 1;
	while (l <= r) {
		m = l + r >> 1;
		int v = f(m);
		if (v >= n) {
			result = std::min(result, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	return result > MAX ? -1 : result;
}

int main() {
	dp[0][0] = 1;
	for (int i = 1; i <= 10; ++i) {
		dp[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
	}
	for (int i = 1; i <= 10; ++i)
		c10[i] = c10[i - 1] + dp[10][i];

	ll N;
	std::cin >> N;
	std::cout << binary_search(N);
}