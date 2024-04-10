#include <iostream>
#include <algorithm>

int N, M, K, A[100];

std::string solve() {
	std::cin >> N >> M >> K;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	std::sort(A, A + N);
	for (int i = 0; i < N; ++i) {
		int remain = (A[i] / M * K) - i;
		if (remain < 1) return "Impossible\n";
	}
	return "Possible\n";
}

int main() {
	int t, T;
	std::cin >> T;
	for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve();
}
