#include <iostream>

const int LEN = 2e5 + 1;

int N, K, T;
int A[LEN], order[LEN];

int main() {
	std::cin >> N >> K >> T;
	for (int i = 0; i < K; ++i) std::cin >> A[i];
	A[K] = N;
	for (int i = 0; i < K; ++i) {
		for (int j = A[i], c = 0, d = A[i + 1] - A[i], e; j < A[i + 1]; ++j, ++c) {
			e = ((c - T) % d + d) % d;
			order[(A[i] + e + T) % N] = j;
		}
	}
	for (int i = 0; i < N; ++i) std::cout << order[i] << ' ';
}