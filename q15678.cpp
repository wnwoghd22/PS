#include <iostream>
#include <queue>

typedef long long int ll;
const int LEN = 100'001;
const ll INF = 1e20;
ll N, K, A[LEN], dp[LEN] = { -INF, };
std::deque<std::pair<ll, int>> dq;

int main() {
	std::cin >> N >> K;
	for (int i = 1; i <= N; ++i) dp[i] = -INF, std::cin >> A[i];

	dq.push_back({ 0, 0 });
	for (int i = 1; i <= N; ++i) {
		while (!dq.empty() && dq.front().second < i - K) dq.pop_front();
		dp[i] = A[i] + dq.front().first;
		std::cout << dp[i] << ' ' << A[i] << ' ' << dq.front().first << '\n';
		while (!dq.empty() && dq.back().first < dp[i]) dq.pop_back();
		dq.push_back({ dp[i], i });
		// dp[i] = std::max(dp[i], dp[i - 1]);
	}
	// std::cout << dp[N];
	std::cout << dq.front().first;
}