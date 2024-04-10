#include <iostream>
#include <queue>
#include <cstring>

const int MAX = 100'000;

int step[MAX * 2 + 1];
int dp[MAX * 2 + 1];

void bfs(int n, int k) {
	std::queue<std::pair<int, int>> q;
	memset(step, -1, sizeof step);
	step[n] = 0;
	dp[n] = 1;
	q.push({ n, 0 });

	while (!q.empty()) {
		n = q.front().first; int s = q.front().second + 1; q.pop();

		if (n == k) break;

		if (n < MAX * 2) {
			if (!~step[n + 1]) {
				step[n + 1] = s;
				dp[n + 1] += dp[n];
				q.push({ n + 1, s });
			}
			else if (s == step[n + 1]) dp[n + 1] += dp[n];
		}
		if (n > 0) {
			if (!~step[n - 1]) {
				step[n - 1] = s;
				dp[n - 1] += dp[n];
				q.push({ n - 1, s });
			}
			else if (s == step[n - 1]) dp[n - 1] += dp[n];
		}
		if (n <= MAX) {
			if (!~step[n << 1]) {
				step[n << 1] = s;
				dp[n << 1] += dp[n];
				q.push({ n << 1, s });
			}
			else if (s == step[n << 1]) dp[n << 1] += dp[n];
		}
	}
}

int main() {
	int N, K;
	std::cin >> N >> K;
	bfs(N, K);
	std::cout << step[K] << '\n' << dp[K];
}