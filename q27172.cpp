#include <iostream>

const int LEN = 1e6 + 1;

bool f[LEN];
int N, A[LEN], S[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> A[i];
		f[A[i]] = 1;
	}
	for (int i = 1; i < LEN; ++i) {
		if (!f[i]) continue;
		for (int j = i * 2; j < LEN; j += i) {
			S[i] += f[j];
			S[j] -= f[j];
		}
	}
	for (int i = 0; i < N; ++i) std::cout << S[A[i]] << ' ';
}