#include <iostream>

int A[8], R[8];
int N, K;

int main() {
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		std::cin >> R[i];
		A[i] = 1;
	}

	if (N % K == 0) {
		for (int i = 0; i < N; ++i) std::cout << A[i] << ' ';
		std::cout << '\n';
	}
	while (1) {
		int flag = 0;
		for (int i = N - 1; i >= 0; --i) {
			A[i] += 1;
			if (A[i] > R[i]) {
				A[i] = 1;
				if (i == 0) flag = true;
			}
			else break;
		}
		if (flag) break;
		int sum = 0;
		for (int i = 0; i < N; ++i) sum += A[i];
		if (sum % K == 0) {
			for (int i = 0; i < N; ++i) std::cout << A[i] << ' ';
			std::cout << '\n';
		}
	}
}