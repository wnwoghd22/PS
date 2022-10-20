#include <iostream>
#include <queue>

typedef long long int ll;
const int LEN = 100'001;
ll N, K, A[LEN], S[LEN], dp[LEN];
std::deque<std::pair<ll, int>> dq;

int main() {
	std::cin >> N >> K;
	for (int i = 1; i <= N; ++i) std::cin >> A[i], S[i] = A[i] + S[i - 1];
	dq.push_back({ 0, 0 });
	for (int i = 1; i <= N; ++i) {
		while (!dq.empty() && dq.front().second < i - K) dq.pop_front();
		dp[i] = S[i] + dq.front().first;
		while (!dq.empty() && dq.back().first < dp[i - 1] - S[i]) dq.pop_back();
		dq.push_back({ dp[i - 1] - S[i], i });
		dp[i] = std::max(dp[i], dp[i - 1]);
	}
	std::cout << dp[N];
}