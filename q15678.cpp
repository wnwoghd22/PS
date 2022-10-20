#include <iostream>
#include <queue>

typedef long long int ll;
const ll INF = 1e15;
ll N, D, K, S, M = -INF;
std::deque<std::pair<ll, int>> dq;

int main() {
	std::cin >> N >> D;
	dq.push_back({ 0, 0 });
	for (int i = 1; i <= N; ++i) {
		std::cin >> K;
		while (!dq.empty() && dq.front().second < i - D) dq.pop_front();
		S = std::max(K, K + dq.front().first);
		M = std::max(S, M);
		while (!dq.empty() && dq.back().first < S) dq.pop_back();
		dq.push_back({ S, i });
	}
	std::cout << M;
}