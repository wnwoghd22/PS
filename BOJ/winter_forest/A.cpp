#include <iostream>
#include <queue>

int main() {
	int N, a, result = 0;
	std::priority_queue<int> q;
	std::cin >> N;
	while (N--) {
		std::cin >> a;
		q.push(a);
	}
	while (q.size() > 1) {
		int a1 = q.top(); q.pop();
		int a2 = q.top(); q.pop();

		result += std::min(a1, a2);
		int remain = std::max(a1, a2) - std::min(a1, a2);
		if (remain) q.push(remain);
	}
	if (q.size()) result += q.top();
	if (result > 1440) std::cout << -1;
	else std::cout << result;
}