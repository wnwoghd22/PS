#include <iostream>

typedef long long ll;
const int LEN = 1001;

int N;
ll dp[LEN], S[LEN];

int main() {
	for (int i = 1; i < LEN; ++i) {
		dp[i] = S[i / 2] + 1;
		S[i] = dp[i] + S[i - 1];
	}
	std::cin >> N;
	for (int i = 0, a; i < N; ++i) {
		std::cin >> a;
		std::cout << dp[a] << '\n';
	}
}