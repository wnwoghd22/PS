#include <iostream>

typedef long long ll;
const int LEN = 2e5 + 1;
const ll MOD = 998'244'353;

int N;
ll a[LEN];
ll S[LEN];
ll inv2;

ll pow(ll a, ll p) {
	ll x = 1;
	while (p) {
		if (p & 1) x = x * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return x;
}

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> a[i], S[i] = S[i - 1] + a[i];
	inv2 = pow(2, MOD - 2);

	ll ex2 = 0;
	ll ex;
	ll se = 0;
	ll ep2 = 0;
	ll ep;
	ll sp = 0;
	for (int i = 1; i <= N; ++i) {
		ex = a[i] * S[i - 1] % MOD * inv2 % MOD;
		
	}
}