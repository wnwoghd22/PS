#include <iostream>
#include <queue>

typedef long long int ll;
const int LEN = 100'001;
const ll INF = 1e15;
ll N, K, A[LEN], dp[LEN], max = -INF;
std::deque<std::pair<ll, int>> dq;

int main() {
	std::cin >> N >> K;
	for (int i = 1; i <= N; ++i) std::cin >> A[i], dp[i] = A[i];

	dq.push_back({ 0, 0 });
	for (int i = 1; i <= N; ++i) {
		while (!dq.empty() && dq.front().second < i - K) dq.pop_front();
		dp[i] = std::max(dp[i], A[i] + dq.front().first);
		max = std::max(dp[i], max);
		std::cout << dp[i] << ' ' << A[i] << ' ' << dq.front().first << '\n';
		while (!dq.empty() && dq.back().first < dp[i]) dq.pop_back();
		dq.push_back({ dp[i], i });
	}

	std::cout << max;
}