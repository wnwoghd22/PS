#include <iostream>
#include <queue>

int main() {
	std::deque<int> dq;
	int N, M, A, max = 0, sum = 0;
	std::cin >> N >> M;

	while (N--) {
		std::cin >> A;
		sum += A;
		dq.push_back(A);
		while (sum > M) {
			sum -= dq.front();
			dq.pop_front();
		}
		max = std::max(sum, max);
	}
	std::cout << max;
}