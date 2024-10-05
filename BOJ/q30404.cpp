#include <iostream>

const int LEN = 1e5;

int N, K, l, r, c, A[LEN];

int main() {
	std::cin >> N >> K >> A[0];
	for (r = 1; r < N; ++r) {
		std::cin >> A[r];
		if (A[r] - A[l] > K) {
			l = r;
			++c;
		}
	}
	std::cout << c + (l <= r);
}