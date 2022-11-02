#include <iostream>

const int LEN = 10001;
int N, A[LEN], B[LEN], C[LEN];

int main() {
	int result = 0;
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];

	for (int b, c, i = 1; i <= N; ++i) {
		b = std::min(B[i - 1], A[i]);
		result += b * 2; A[i] -= b; C[i] += b;

		c = std::min(C[i - 1], A[i]);
		result += c * 2; A[i] -= c;

		B[i] += A[i]; result += B[i] * 3;
	}
	std::cout << result;
}