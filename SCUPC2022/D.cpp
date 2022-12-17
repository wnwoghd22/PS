#include <iostream>
#include <map>

typedef long long int ll;
ll N, X, T, C, R = 0;
std::map<ll, ll> dp;

int main() {
	std::cin >> N;
	while (N--) {
		std::cin >> X >> T >> C;
		ll delta = X - T;
		if (dp.find(delta) == dp.end()) dp[delta] = C;
		else dp[delta] += C;
		R = std::max(R, dp[delta]);
	}
	std::cout << R;
}