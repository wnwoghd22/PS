#include <iostream>
#include <queue>

typedef std::pair<int, int> pii;

/* int main() { // O(N log N)
	std::priority_queue<pii, std::vector<pii>, std::greater<>> pq;
	int N, L;
	std::cin >> N >> L;
	for (int i = 1; i <= N; ++i) {
		int A;
		std::cin >> A;
		pq.push({ A, i });
		while (!pq.empty() && pq.top().second <= i - L) pq.pop();
		std::cout << pq.top().first << ' ';
	}
} */

int main() { // O(N)
	std::deque<pii> dq;
	int N, L;
	std::cin >> N >> L;
	for (int A, i = 1; i <= N; ++i) {
		std::cin >> A;
		while (!dq.empty() && dq.front().second <= i - L) dq.pop_front();
		while (!dq.empty() && dq.back().first > A) dq.pop_back();
		dq.push_back({ A, i });
		std::cout << dq.front().first << ' ';
	}
}