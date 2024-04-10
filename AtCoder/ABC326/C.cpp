#include <iostream>
#include <algorithm>

const int LEN = 3e5;
int N, M, A[LEN], X;

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	std::sort(A, A + N);
	for (int l = 0, r = 0; r < N; ++l) {
		while (r < N && A[r] < A[l] + M) ++r;
		X = std::max(X, r - l);
	}
	std::cout << X;
}