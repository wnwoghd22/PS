#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const ll MOD = 1e13;
ll N;
ll mulmod(ll a, ll b) {
	ll res = 0;
	a = a % MOD;
	while (b) {
		if (b & 1)
			res = (res + a) % MOD;
		a = (a << 1) % MOD;
		b >>= 1;
	}
	return res % MOD;
}

struct Matrix {
	ll a[2][2];
	Matrix(ll arr[2][2]) {
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				a[i][j] = arr[i][j];
	}
	Matrix operator*(const Matrix& r) const {
		ll result[2][2] = { 0, 0, 0, 0 };
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				for (int k = 0; k < 2; ++k)
					result[i][j] += mulmod(a[i][k], r.a[k][j]),
					result[i][j] %= MOD;
		return result;
	}
};

ll dp[1500] = { 0, 1, };
ll id[2][2] = { 1, 0, 0, 1 };
ll unit[2][2] = { 1, 1, 1, 0 };

ll fibo(ll i) {
	Matrix result = id;
	Matrix m = unit;
	while (i) {
		if (i & 1) 
			result = result * m;
		m = m * m;
		i >>= 1;
	}
	return result.a[1][0];
}

std::vector<ll> f(ll n, ll k) {
	std::vector<ll> result;
	if (k <= 3) {
		for (int i = 0; i < 1500; ++i)
			if (n % 1000 == dp[i])
				result.push_back(i);
	}
	else {
		std::vector<ll> v = f(n, k - 1);
		ll p = 15, mod = 100;
		for (int i = 2; i < k; ++i) p *= 10, mod *= 10;

		for (const ll& i : v) {
			for (int m = 0; m < 10; ++m) {
				if (fibo(i + p * m) % mod == n % mod)
					result.push_back(i + p * m);
			}
		}
	}
	std::sort(result.begin(), result.end());
	return result;
}

ll solve(ll n) {
	if (n == MOD) return -1;

	std::vector<ll> v = f(n, 13);
	if (v.size()) return v[0];

	return -1;
}

int main() {
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	for (int i = 2; i < 1500; ++i) dp[i] = (dp[i - 1] + dp[i - 2]) % 1000;
	
	int T;
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		std::cout << solve(N) << '\n';
	}
}
