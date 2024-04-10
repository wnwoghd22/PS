#include <iostream>
#include <algorithm>

const int LEN = 300'001;
int N, A[LEN];
int outlier, ret;
double S;

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	std::sort(A, A + N);
	outlier = (N * 15 + 50) / 100;
	for (int i = outlier; i < N - outlier; ++i) S += A[i];
	ret = (S / (N - outlier * 2) * 10 + 5) / 10;
	std::cout << ret;
}