#include <iostream>

typedef long long ll;
const ll P = 99991;
const ll A = 55048, B = 44944, C = 22019;

const int LEN = 3000001;
ll dp[LEN] = { 0, 1, };

ll pow(ll a, ll b, ll m) {
	ll r = 1;
	while (b) {
		if (b & 1)
			r = r * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return r;
}
ll fibo(ll n) { return (pow(A, n, P) - pow(B, n, P) + P) * C % P; }

int main() {
	for (int i = 2; i < LEN; ++i) {
		dp[i] = (dp[i - 1] + dp[i - 2]) % P;
		if (dp[i] == 1 && dp[i - 1] == 0) {
			std::cout << i;
			break;
		}
	}

}