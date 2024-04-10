#include <iostream>

int N, P[48], S[48], A[48];

bool shuffle() {
	static int B[48];
	bool cycle = 1;
	for (int i = 0; i < N; ++i) B[S[i]] = A[i];
	for (int i = 0; i < N; ++i) A[i] = B[i], cycle &= A[i] == i;
	return cycle;
}

bool check() {
	for (int i = 0; i < N; ++i) {
		if (i % 3 != P[A[i]])
			return 0;
	}
	return 1;
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) A[i] = i;
	for (int i = 0; i < N; ++i) std::cin >> P[i];
	for (int i = 0; i < N; ++i) std::cin >> S[i];
	for (int i = 0, j = 0; !j; ++i) {
		if (check()) {
			std::cout << i;
			break;
		}
		if (shuffle()) {
			std::cout << -1;
			break;
		}
	}
}