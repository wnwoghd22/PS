#include <iostream>

const int MAX = 100'001;
int N, M, X, A, K, S[MAX], l, r;

int main() {
	std::cin >> N >> M >> K >> X;

	for (int i = 1; i <= N; ++i) {
		std::cin >> A;
		X += A;
		S[i] = S[i - 1] + (X < K);
	}
	for (int i = 1; i <= N; ++i) {
		std::cout << S[i] << ' ';
	}
	std::cout << '\n';

	while (M--) {
		std::cin >> l >> r;
		std::cout << S[r - 1] - S[l - 1] << '\n';
	}
}