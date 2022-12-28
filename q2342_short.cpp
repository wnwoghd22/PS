#include <iostream>
#include <algorithm>

const int INF = 1e9;
int dp[5] = { 0, INF, INF, INF, INF };
int cost(int a, int b) { return a == b ? 1 : !a ? 2 : abs(a - b) == 2 ? 4 : 3; }
int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	int a = 0, b, c, d;
	for (std::cin >> b; b; a = b, std::cin >> b) {
		c = cost(a, b), d = INF;
		for (int i = 0; i < 5; ++i) d = std::min(d, dp[i] + cost(i, b)), dp[i] += c;
		dp[a] = d;
	}
	std::cout << *std::min_element(dp, dp + 5);
}