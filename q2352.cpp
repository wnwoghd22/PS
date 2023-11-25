#include <iostream>

const int LEN = 4e4 + 1;

int N, M, A[LEN], len, dp[LEN];

char c;

int lower_bound(int x) {
	int l = 0, r = len, m;
	while (l < r) {
		m = l + r >> 1;
		if (dp[m] < x) l = m + 1;
		else r = m;
	}
	return r;
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];

	for (int i = 0; i < N; ++i) {
		int j = lower_bound(A[i]);
		if (j < len) dp[j] = A[i];
		else dp[len++] = A[i];
	}
	std::cout << len;
}