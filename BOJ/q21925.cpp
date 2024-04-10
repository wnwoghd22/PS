#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 5001;

bool p[LEN][LEN];

int N, A[LEN], dp[LEN];

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	memset(dp, -1, sizeof dp);

	for (int i = 1; i < N; ++i) {
		p[i][i + 1] = A[i] == A[i + 1];
		for (int s = i - 1, e = i + 2; s > 0 && e <= N; --s, ++e)
			p[s][e] = p[s + 1][e - 1] && (A[s] == A[e]);
	}
	
	dp[0] = 0;
	for (int i = 2; i <= N; i += 2) {
		for (int j = 0; j < i; j += 2) {
			if (!~dp[j] || !p[j + 1][i]) continue;
			dp[i] = std::max(dp[i], dp[j] + 1);
		}
	}

	std::cout << dp[N];
}