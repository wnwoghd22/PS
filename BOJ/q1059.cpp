#include <iostream>
#include <algorithm>

int l, r, L, N, A[51];
int main() {
	std::cin >> L;
	for (int i = 1; i <= L; ++i) std::cin >> A[i];
	std::cin >> N;
	std::sort(A, A + L + 1);
	for (int i = 0; i <= L; ++i) {
		if (A[i] <= N) l = i;
		if (A[i] > N) {
			r = i;
			break;
		}
	}
	if (A[l] == N) std::cout << 0;
	else {
		int K = A[r] - A[l] - 1;
		l = N - A[l] - 1;
		r = A[r] - N - 1;
		std::cout << (K * (K - 1) >> 1) - (l * (l - 1) >> 1) - (r * (r - 1) >> 1);
	}
}


