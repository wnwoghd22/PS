#include <iostream>
#include <vector>
#include <queue>

typedef unsigned long long ll;
const ll MOD = 1e18;
const ll STEP = 15e17;
std::string S;
ll N, mod = 1;
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

struct Info {
	ll i, d;
	bool operator<(const Info& r) const { return i > r.i; }
};

int main() {
	std::cin >> S;
	for (const char& c : S)
		N = N * 10 + c - '0', mod *= 10;
	
	for (int i = 2; i < 1500; ++i) dp[i] = (dp[i - 1] + dp[i - 2]) % 1000;
	if (S.length() < 3) {
		if (S.length() == 1) {
			for (ll i = 0; i < 1500; ++i) {
				if (N == dp[i] % 10) {
					std::cout << i;
					return 0;
				}
			}
		}
		if (S.length() == 2 && S[0] != '0') {
			for (ll i = 0; i < 1500; ++i) {
				if (N == dp[i] % 100) {
					std::cout << i;
					return 0;
				}
			}
		}
	}

	std::priority_queue<Info> q;
	for (ll i = 0; i < 1500; ++i)
		if (N % 1000 == dp[i])
			q.push({ i, 3 });

	while (q.size()) {
		ll i = q.top().i, d = q.top().d; q.pop();
		// std::cout << i << '\n';
		if (fibo(i + STEP) % mod == N % mod) {
			std::cout << i + STEP;
			return 0;
		}
		ll p = 15, mod = 100;
		for (int i = 1; i < d; ++i) p *= 10, mod *= 10;

		for (int k = 0; k < 10; ++k) {
			if (fibo(i + p * k) % mod == N % mod)
				q.push({ i + p * k, d + 1 });
		}
	}
	std::cout << "NIE";
}