#include <iostream>
#include <queue>

int N;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;

	std::priority_queue<int> pq;
	for (int i = 0, a; i < N * N; ++i) {
		std::cin >> a;
		if (pq.size() >= N) {
			if (-pq.top() < a) {
				pq.pop();
				pq.push(-a);
			}
		}
		else pq.push(-a);
	}
	std::cout << -pq.top();
}