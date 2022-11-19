#include <iostream>
#include <algorithm>

int N, L, R, S = 2e9, A[100'000];
int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	int l = 0, r = N - 1, L = l, R = r, s;
	while (l < r) {
		s = A[l] + A[r];
		if (abs(s) < S) S = abs(s), L = l, R = r;
		if (!s) break;
		else if (s > 0) --r;
		else ++l;
	}
	std::cout << A[L] << ' ' << A[R];
}