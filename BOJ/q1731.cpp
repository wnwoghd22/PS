#include <iostream>

typedef long long ll;
ll N, A[50];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	if (A[0] * A[2] == A[1] * A[1]) std::cout << A[N - 1] * A[1] / A[0];
	if (A[2] - A[1] == A[1] - A[0]) std::cout << A[N - 1] + A[1] - A[0];
}