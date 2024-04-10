#include <iostream>
#include <unordered_map>
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

const int LEN = 1'000'001;
int phi[LEN];
std::unordered_map<int, ll> dp;
void init() {
	for (int i = 0; i < LEN; ++i) phi[i] = i;
	for (int i = 2; i < LEN; ++i) {
		if (phi[i] == i) {
			for (int j = i; j < LEN; j += i)
				phi[j] /= i, phi[j] *= i - 1;
		}
	}
	dp[0] = 0;
	for (int i = 1; i < LEN; ++i) dp[i] = dp[i - 1] + phi[i];
}
ll Sp(int i) {
	if (dp.find(i) != dp.end()) return dp[i];
	ll s = (i + 1ll) * i >> 1;
	for (ll d = 2, j; d <= i; d = j + 1) {
		j = i / (i / d);
		s -= (j - d + 1) * Sp(i / d);
	}
	return dp[i] = s;
}

int main() {
	init();
	int T;
	std::cin >> T;
	while (T--) {
		int N;
		std::cin >> N;
		ll result = 0;
		for (int i = 1, j; i <= N; i = j + 1) {
			j = N / (N / i);
			result += ((Sf(j) - Sf(i - 1) + MOD) % MOD) * ((Sp(N / i) * 2 - 1) % MOD) % MOD;
			result %= MOD;
		}
		std::cout << result << '\n';
	}
}