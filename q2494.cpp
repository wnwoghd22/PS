#include <iostream>
#include <algorithm>
#include <vector>

const int LEN = 10'001;
const int INF = 1e9;
int dp[LEN][10];
char s[LEN], t[LEN];
int N;

int F(std::vector<int>& v) {
	for (int i = 1; i <= N; ++i)
		for (int j = 0; j < 10; ++j)
			dp[i][j] = INF;
	for (int i = 0; i < 10; ++i) dp[0][i] = i;

	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j < 10; ++j) {
			int left = (t[i - 1] - s[i - 1] - j + 20) % 10;
			int right = 10 - left;

			dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + right);
			dp[i][(j + left) % 10] = std::min(dp[i][(j + left) % 10], dp[i - 1][j] + left);
		}
	}

	for (int j = 0; j < 10; ++j) {
		for (int i = 1; i <= N; ++i) {
			std::cout << dp[i][j] << ' ';
		}
		std::cout << '\n';
	}
	int min_pos = std::min_element(dp[N], dp[N] + 10) - dp[N];
	std::cout << min_pos << '\n';

	int k = min_pos;
	for (int i = N; i >= 2; --i) {
		if (dp[i - 1][k] <= dp[i][k]) {
			std::cout << dp[i - 1][k] << ' ' << dp[i][k] << '\n';
			v.push_back(dp[i - 1][k] - dp[i][k]);
			continue;
		}
		for (int j = 0; j < 10; ++j) {
			int pre = (k + 10 - j) % 10;
			std::cout << "pre: " << pre << '\n';
			if (dp[i][k] - j == dp[i - 1][pre]) {
				v.push_back(j);
				k = pre;
				break;
			}
		}
	}
	v.push_back(k ? k : -dp[1][k]);

	return dp[N][min_pos];
}

int main() {
	std::cin >> N >> s >> t;
	std::vector<int> rotation;
	std::cout << F(rotation) << '\n';

	for (int i = 1; i <= N; ++i) {
		std::cout << i << ' ' << rotation[N - i] << '\n';
	}
}