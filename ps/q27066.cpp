#include <iostream>
#include <algorithm>

const int LEN = 100'001;
int N;
double sum;
int A[LEN];

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i], sum += A[i];
	std::sort(A + 1, A + N + 1);
	std::cout << std::fixed;
	std::cout.precision(7);
	std::cout << std::max((double)A[N - 1], sum / N);
}