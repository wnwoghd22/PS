#include <iostream>
#include <queue>

std::priority_queue<int> Q;
int N, M, c, w;

int main() {
	std::cin >> N >> M;
	while (N--) {
		std::cin >> c;
		Q.push(c);
	}
	while (M--) {
		std::cin >> w;
		c = Q.top(); Q.pop();
		if (w > c) {
			std::cout << 0;
			return 0;
		}
		Q.push(c - w);
	}
	std::cout << 1;
}

