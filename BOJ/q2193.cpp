#include <iostream>

typedef long long int ll;
ll dp[90][2] = { 1, 1 };

int main() {
	for (int i = 1; i < 90; ++i) {
		dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
		dp[i][1] = dp[i - 1][0];
	}
	int n;
	std::cin >> n;
	std::cout << dp[n - 1][1];
}