#include <iostream>
#include <algorithm>

int A[200000], B[200000];
int N;

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		for (int i = 0; i < N; ++i) {
			std::cin >> A[i];
			B[i] = A[i];
		}
		std::sort(B, B + N);
		for (int i = 0; i < N; ++i) {
			if (A[i] != B[N - 1]) std::cout << A[i] - B[N - 1] << ' ';
			else std::cout << A[i] - B[N - 2] << ' ';
		}
		std::cout << '\n';
	}
}