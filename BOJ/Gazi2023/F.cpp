#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long ll;
const int LEN = 5e5;
ll gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

ll N, A[LEN], dp[LEN][4];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	dp[0][0] = dp[0][1] = A[0];
	dp[0][2] = dp[0][3] = A[1];
	for (int i = 1; i < N; ++i) {

	}
}