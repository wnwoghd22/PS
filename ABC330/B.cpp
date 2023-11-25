#include <iostream>

int N, A, L, R;

int main() {
	std::cin >> N >> L >> R;
	for (int i = 0; i < N; ++i) {
		std::cin >> A;
		if (A < L) std::cout << L << ' ';
		if (A > R) std::cout << R << ' ';
		if (L <= A && A <= R) std::cout << A << ' ';
	}
}