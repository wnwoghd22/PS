#include <iostream>

int N, K, A[100];

int main() {
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	for (int i = 0; i < N; ++i) {
		std::cout << A[(N - K + i) % N] << ' ';
	}
}