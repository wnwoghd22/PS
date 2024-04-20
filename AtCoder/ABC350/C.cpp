#include <iostream>

const int LEN = 2e5 + 1;

int N, A[LEN], O[LEN];
int cnt, x[LEN], y[LEN];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> A[i];
		O[A[i]] = i;
	}
	for (int i = 0, j; i < N; ++i) {
		if (A[i] == i + 1) continue;
		j = O[i + 1];
		O[A[i]] = j;
		A[j] = A[i];
		A[i] = i + 1;
		x[cnt] = i + 1; y[cnt] = j + 1;
		cnt++;
	}
	std::cout << cnt << '\n';
	for (int i = 0; i < cnt; ++i) std::cout << x[i] << ' ' << y[i] << '\n';
}