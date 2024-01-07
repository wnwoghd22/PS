#include <iostream>

const int LEN = 250'000;
int N, X, S, A[LEN], M, C;

int main() {
	std::cin >> N >> X;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	for (int i = 0; i < X - 1; ++i) S += A[i];
	for (int i = X, j = 0; i < N; ++i) {
		S += A[i];
		if (S > M) M = S, C = 1;
		else if (S == M)++C;
		S -= A[j++];
	}
	if (M == 0) std::cout << "SAD";
	else std::cout << M << '\n' << C;
}