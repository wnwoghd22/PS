#include <iostream>

const int LEN = 1e5;

int N, K, A[LEN];

int main() {
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	int cnt = 0;
	for (int i = 1; i < N; ++i) {
		if (A[i] > A[i - 1]) continue;
		if (A[i] + K <= A[i - 1]) {
			cnt = -1;
			break;
		}
		A[i] += K;
		++cnt;
	}
	std::cout << cnt;
}