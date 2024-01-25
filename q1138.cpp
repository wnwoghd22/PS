#include <iostream>

int N, A[10];

int main() {
	std::cin >> N;
	for (int i = 0, a; i < N; ++i) {
		std::cin >> a;
		for (int j = 0, k = 0; j < N; ++j) {
			if (A[j]) continue;
			if (k == a) {
				A[j] = i + 1;
				break;
			}
			else ++k;
		}
	}
	for (int i = 0; i < N; ++i) std::cout << A[i] << ' ';
}