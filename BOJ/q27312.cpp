#include <iostream>

const int LEN = 1001;
int M, N, Q;
int A[LEN];

int main() {
	std::cin >> M >> N >> Q;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	for (int q = 0, a; q < M; ++q) {
		std::cout << "? " << q + 1 << ' ' << q + 1 << std::endl;
		std::cin >> a;
		a++;
		if (a > A[q]) a = 1;
		A[q] = a;
	}
	std::cout << "! ";
	for (int i = 0; i < N; ++i) std::cout << A[i] << ' ';
	std::cout << std::endl;
}