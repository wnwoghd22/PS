#include <iostream>
#include <algorithm>

int N, K, f[50];
struct E {
	int i, w;
	bool operator<(const E& o) const {
		return w > o.w;
	}
} A[50];

int main() {
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) std::cin >> A[i].w, A[i].i = i;
	std::sort(A, A + N);
	int ret = 0;
	for (int i = std::min(N, K) - 1; i >= 0; --i) {
		std::cout << A[i].i + 1 << '\n';
		f[A[i].i] = A[i].i + 1;
	}
	if (K > N) {
		for (int i = 0; i < K - N; ++i)
			std::cout << "0\n";
	}
	for (int i = 0; i < N; ++i) std::cout << f[i] << '\n';
}