#include <iostream>
#include <algorithm>

typedef long long int ll;
const int LEN = 2e5;
ll N, A[LEN];

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		for (int i = 0; i < N; ++i) std::cin >> A[i];
		std::sort(A, A + N);
		if (A[N / 2 - 1] == A[N / 2]) {
			ll l = 1, r = 1;
			for (int i = N / 2 - 2; i >= 0; --i) {
				if (A[i] == A[i + 1]) ++l;
				else break;
			}
			for (int i = N / 2 + 1; i < N; ++i) {
				if (A[i] == A[i - 1]) ++r;
				else break;
			}
			ll result = std::max((N / 2 - l) * (N - N / 2 + l), (N / 2 + r) * (N - N / 2 - r));
			std::cout << (result ? result : N / 2) << '\n';
		}
		else std::cout << (N / 2) * (N - N / 2) << '\n';
	}
}