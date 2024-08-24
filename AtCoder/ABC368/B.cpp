#include <iostream>
#include <queue>

int N, A, B;

int main() {
	std::cin >> N;
	std::priority_queue<int> pq;
	for (int i = 0; i < N; ++i) {
		std::cin >> A;
		pq.push(A);
	}
	int ret = 0;
	while (1) {
		A = pq.top(); pq.pop();
		B = pq.top(); pq.pop();
		if (A <= 0 || B <= 0) break;
		// std::cout << A << ' ' << B << '\n';
		A--; B--;
		pq.push(A); pq.push(B);
		ret++;
	}
	std::cout << ret;
}