#include <iostream>

typedef long long ll;
ll N, C, K, A[50];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	std::cin >> K;
	for (int i = 0; i < N; ++i) C += (A[i] + K - 1) / K;
	std::cout << C * K;
}