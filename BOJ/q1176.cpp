#include <iostream>
#include <algorithm>
#include <string>

typedef long long ll;

ll dp[16][1 << 16];
int N, K, H[16];

ll f(int i, int b) {
	if (b == (1 << N) - 1) return 1;
	ll& ref = dp[i][b];
	if (~ref) return ref;
	ref = 0;
	for (int j = 0; j < N; ++j) {
		if (b & 1 << j) continue;
		if (std::abs(H[i] - H[j]) > K)
			ref += f(j, b | 1 << j);
	}
	return ref;
}

int main() {
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i)
		std::cin >> H[i];
	ll ret = 0;
	memset(dp, -1, sizeof dp);
	for (int i = 0; i < N; ++i)
		ret += f(i, 1 << i);
	std::cout << ret;
}