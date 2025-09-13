#include <iostream>
#include <cstring>

const int LEN = 1001;
int T, N, S[LEN], dp[LEN][LEN];

int f(int l, int r) {
	if (l == r) return S[r] - S[l - 1];
	int& ret = dp[l][r];
	if (~ret) return ret;
	return ret = S[r] - S[l - 1] - std::min(f(l + 1, r), f(l, r - 1));
}

int solve() {
	memset(dp, -1, sizeof dp);
	std::cin >> N;
	for (int i = 1, a; i <= N; ++i) {
		std::cin >> a;
		S[i] = a + S[i - 1];
	}
	return f(1, N);
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';
}