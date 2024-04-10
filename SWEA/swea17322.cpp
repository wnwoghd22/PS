#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define ll long long
#define MOD 1000000007

ll pow(ll a, int p) {
	ll x = 1;
	while (p) {
		if (p & 1) x = x * a % MOD;
		a = a * a % MOD;
		p >>= 1;
	}
	return x;
}
int odd[333334] = { 1, };
ll f(int n) {
	if (n <= 1) return 1;
	return odd[n - 1 >> 1] * f(n >> 1) % MOD * pow(2, n >> 1) % MOD;
}

int main() {
	for (int i = 1; i <= 333333; ++i) odd[i] = (ll)(i << 1 | 1) * odd[i - 1] % MOD;
	int t, T, x, y, n, k, p, r;
	scanf("%d", &T);
	for (t = 1; t <= T; ++t) {
		scanf("%d%d", &x, &y);
		if ((x + y) % 3 || x > (y << 1) || y > (x << 1)) r = 0;
		else {
			n = (x + y) / 3;
			k = x - n;
			x = f(n);
			y = (ll)f(k) * f(n - k) % MOD;
			p = pow(y, MOD - 2);
			r = (ll)x * p % MOD;
		}
		printf("#%d %d\n", t, r);
	}
}