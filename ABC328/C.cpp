#include <iostream>

const int LEN = 3e5 + 1;
char S[LEN];
int N, Q, sum[LEN];

int main() {
	std::cin >> N >> Q >> S;
	for (int i = 0; i < N - 1; ++i) {
		if (S[i] == S[i + 1]) sum[i + 1] = 1;
		sum[i + 1] += sum[i];
		// std::cout << sum[i + 1] << ' ';
	}
	for (int i = 0, l, r; i < Q; ++i) {
		std::cin >> l >> r;
		std::cout << sum[r - 1] -sum[l - 1] << '\n';
	}
}