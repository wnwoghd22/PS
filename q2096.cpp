#include <iostream>
#include <algorithm>

int max_dp[3];
int min_dp[3];

int main() {
	int N, input[3], temp_max[3], temp_min[3];
	std::cin >> N;

	while (N--) {
		for (int i = 0; i < 3; ++i) std::cin >> input[i];

		temp_max[0] = std::max(max_dp[0], max_dp[1]) + input[0];
		temp_min[0] = std::min(min_dp[0], min_dp[1]) + input[0];

		temp_max[1] = std::max({ max_dp[0], max_dp[1], max_dp[2] }) + input[1];
		temp_min[1] = std::min({ min_dp[0], min_dp[1], min_dp[2] }) + input[1];

		temp_max[2] = std::max(max_dp[1], max_dp[2]) + input[2];
		temp_min[2] = std::min(min_dp[1], min_dp[2]) + input[2];

		for (int i = 0; i < 3; ++i) max_dp[i] = temp_max[i], min_dp[i] = temp_min[i];
	}
	std::cout << *std::max_element(max_dp, max_dp + 3) << ' ' << *std::min_element(min_dp, min_dp + 3);
}