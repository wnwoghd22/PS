#include <iostream>

int A[200000];
int N, R, L;

int main() {
	std::cin >> N >> L >> R;
	int result = 0;
	for (int i = 0; i < N; ++i) {
		std::cin >> A[i];
		int r = A[i] % (L + R) / L;
		result ^= r;
	}
	std::cout << (result ? "First" : "Second");
}
