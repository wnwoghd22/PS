#include <iostream>

int N, A[100];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	std::cout << A[0] << ' ';
	for (int i = 1; i < N; ++i) {
		if (A[i - 1] < A[i])
			for (int j = A[i - 1] + 1; j < A[i]; ++j)
				std::cout << j << ' ';
		else
			for (int j = A[i - 1] - 1; j > A[i]; --j)
				std::cout << j << ' ';

		std::cout << A[i] << ' ';
	}
}