#include <iostream>

int N, M, K, cur, i, t, r;

int main() {
	std::cin >> N >> M >> K;
	for (i = 1; i <= M; ++i) {
		std::cin >> t >> r;
		if ((cur += r) > K) break;
	}
	if (i <= M) std::cout << i << ' ' << 1;
	else std::cout << -1;
}