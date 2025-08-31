#include <iostream>

int N, A[200'001];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	if (N == 1) {
		std::cout << 1;
		return 0;
	}

	for (int i = 0; i < N; ++i) std::cin >> A[i];
	int b = -1e9, c = 0;
	for (int i = N - 1; i; --i) {
		int f = 0;
		if (A[i] > A[i - 1] && A[i] > b) f = 1, c++;
		b = std::max(b, A[i] - i + 1);
		if (f) A[i] = -1;
	}
	if (c) {
		for (int i = 0; i < N; ++i) {
			if (A[i] < 0) std::cout << i + 1 << ' ';
		}
	}
	else std::cout << -1;
}