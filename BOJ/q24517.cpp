#include <iostream>
#include <cstring>

int dp[56][1 << 10];
int Q, A, B, K;

int f(int n, int b) {
	if (n <= 0) return 0;
	int& ref = dp[n][b];
	if (~ref) return ref;
	ref = 1;
	for (int i = 0; i < 10; ++i) {
		if (~b & 1 << i)
			ref &= f(n - i - 1, b | 1 << i);
	}
	return ref ^= 1;
}

int qry(int a, int b, int k) {
	int n = b - a;
	int s = k * (k + 1) / 2;
	int games = n / s;
	int ret = f(n % s, 1024 - (1 << k));
	return ret ^ (games & k & 1);
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	memset(dp, -1, sizeof dp);

	std::cin >> Q;
	for (int q = 0; q < Q; ++q) {
		std::cin >> A >> B >> K;
		std::cout << (qry(A, B, K) ? "swoon" : "raararaara") << '\n';
	}
}