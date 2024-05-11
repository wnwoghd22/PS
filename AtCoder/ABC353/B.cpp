#include <iostream>

int main() {
	int N, K, A;
	int cnt = 0, k = 0;
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		std::cin >> A;
		if (k + A > K) {
			cnt++;
			k = A;
		}
		else if (k + A == K) {
			cnt++;
			k = 0;
		}
		else k += A;
	}
	if (k > 0) cnt++;
	std::cout << cnt;
}