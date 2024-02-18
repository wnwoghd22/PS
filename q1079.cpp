#include <iostream>
#include <algorithm>

int N, P, A[16], R[16][16], ret;

void f(int n, int b, int r) {
	ret = std::max(ret, r);
	if (n <= 1 || (b & 1 << P)) return;
	if (~n & 1) { // night
		for (int i = 0; i < N; ++i) {
			if (i == P) continue;
			if (b & 1 << i) continue;
			for (int j = 0; j < N; ++j) A[j] += R[i][j];
			f(n - 1, b | 1 << i, r + 1);
			for (int j = 0; j < N; ++j) A[j] -= R[i][j];
		}
	}
	else { // day
		int i;
		for (i = 0; i < N; ++i) if (~b & 1 << i) break;
		for (int j = i + 1; j < N; ++j) {
			if (b & 1 << j) continue;
			if (A[j] > A[i]) i = j;
		}
		f(n - 1, b | 1 << i, r);
	}
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			std::cin >> R[i][j];
	std::cin >> P;
	f(N, 0, 0);
	std::cout << ret;
}