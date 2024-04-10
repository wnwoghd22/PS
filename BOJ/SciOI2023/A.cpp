#include <iostream>

int T, N, M, K;

int main() {
	std::cin >> T;
	while (T--) {
		std::cin >> N >> M >> K;
		if (K == 1 && M < N) std::cout << "-1\n";
		else {
			int cnt = 0;
			while (1) {
				cnt++;
				N -= M * K;
				if (N <= 0) break;
				cnt++;
				++N;
			}
			std::cout << cnt << '\n';
		}
	}
}