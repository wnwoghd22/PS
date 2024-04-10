#include <iostream>
#include <algorithm>

typedef long long int ll;
const ll MOD = 1e9 + 7;
const int LEN = 3e5;
ll pow(ll x, ll n) {
	if (n == 0) return 1;
	if (n == 1) return x % MOD;
	ll p = pow(x, n >> 1);
	return p * p % MOD * (n & 1 ? x : 1) % MOD;
}

ll N, result, A[LEN];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	std::sort(A, A + N);
	for (int i = 0; i < N; ++i) {
		result += (pow(2, i) - pow(2, N - i - 1)) * A[i] + MOD;
		result %= MOD;
	}
	std::cout << result;
}