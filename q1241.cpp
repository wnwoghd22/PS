#include <iostream>

const int LEN = 1e5;
const int MAX = 1e6 + 1;

int N, A[LEN], C[MAX], S[MAX];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> A[i];
		C[A[i]]++;
	}
	for (int i = 1; i < MAX; ++i) {
		for (int j = i; j < MAX; j += i)
			S[j] += C[i];
	}
	for (int i = 0; i < N; ++i) std::cout << S[A[i]] - 1 << '\n';
}