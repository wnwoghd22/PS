#include <iostream>
#include <queue>

int main() {
	std::queue<int> Q;
	int N, q;
	std::cin >> N;
	do {
		std::cin >> q;
		if (!q) {
			if (!Q.empty()) Q.pop();
		}
		else if (q > 0) {
			if (Q.size() < N) Q.push(q);
		}
	} while (~q);

	if (Q.empty()) std::cout << "empty";
	else while (Q.size()) std::cout << Q.front() << ' ', Q.pop();
}