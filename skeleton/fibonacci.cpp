#include <iostream>
#include <vector>

typedef long long ll;
const ll MOD = 1e9 + 7;

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
					result[i][j] += a[i][k] * r.a[k][j] % MOD,
					result[i][j] %= MOD;
		return result;
	}
};

ll result;
ll dp[1500] = { 0, 1, };
ll id[2][2] = { 1, 0, 0, 1 };
ll unit[2][2] = { 1, 1, 1, 0 };

ll fibo(int i) {
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

ll Sf(int i) { return fibo(i + 2) - 1; }
