#include <iostream>

typedef long long ll;
const int LEN = 2e5 + 1;
const ll MOD = 998'244'353;

int N;
ll a[LEN];
ll S[LEN];
ll inv2, inv3, inv4;

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
	inv2 = pow(2ll, MOD - 2);
	inv3 = pow(3ll, MOD - 2);
	inv4 = pow(4ll, MOD - 2);
	// std::cout << inv2 << ' ' << inv3 << ' ' << inv4 << '\n';

	ll result = 0;
	ll ex2 = 0;
	ll ex, s = 0;
	for (int i = 1; i <= N; ++i) {
		ex = a[i] * S[i - 1] % MOD * inv2 % MOD;
		ex2 = a[i] * S[i - 1] % MOD * inv2 % MOD
			+ a[i] * (a[i] - 1 + MOD) % MOD * S[i - 1] % MOD * (S[i - 1] - 1 + MOD) % MOD * inv4 % MOD 
			+ a[i] * S[i - 1] % MOD * (a[i] + S[i - 1] - 2 + MOD) % MOD * inv3 % MOD;
		result = (result + 2 * ex * s % MOD + ex2) % MOD;
		// std::cout << a[i] << ' ' << S[i] << ' ' << ex << ' ' << ex2 << '\n';
		s = (s + ex) % MOD;
	}
	std::cout << result;
}