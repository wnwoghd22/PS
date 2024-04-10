#include <iostream>

int N, M, i, j, A[101], temp[101];

int main() {
	std::cin >> N >> M;
	for (i = 1; i <= N; ++i) A[i] = i;
	while (M--) {
		std::cin >> i >> j;
		for (int k = i; k <= j; ++k) temp[k] = A[j - k + i];
		for (int k = i; k <= j; ++k) A[k] = temp[k];
	}
	for (i = 1; i <= N; ++i) std::cout << A[i] << ' ';
}