#include <iostream>
#include <vector>

typedef long long ll;
typedef std::vector<ll> Poly;
const ll MOD = 1e9 + 7;

ll power(ll a, ll b) {
	ll p = 1;
	while (b) {
		if (b & 1) p = p * a % MOD;
		b >>= 1; a = a * a % MOD;
	}
	return p;
}

Poly Mul(const Poly& a, const Poly& b) {
	Poly result(a.size() + b.size() - 1);
	for (int i = 0; i < a.size(); ++i)
		for (int j = 0; j < b.size(); ++j) {
			result[i + j] += a[i] * b[j];
			result[i + j] %= MOD;
		}
	return result;
}
Poly Div(const Poly& a, const Poly& b) {
	Poly result(a.begin(), a.end());
	for (int i = a.size() - 1; i >= b.size() - 1; --i)
		for (int j = 0; j < b.size(); ++j) {
			result[i - b.size() + j + 1] += MOD * MOD - result[i] * b[j];
			result[i - b.size() + j + 1] %= MOD;
		}
	result.resize(b.size() - 1);
	return result;
}

Poly kitamasa(const Poly& c, ll n) {
	Poly d = { 1 }; // result
	Poly xn = { 0, 1 }; // xn = x^1, x^2, x^4, ...
	Poly f(c.size() + 1); f.back() = 1;
	for (int i = 0; i < c.size(); ++i) {
		f[i] = -c[i]; // f(x) = x^k - \sum c_i x^i
		f[i] = (f[i] + MOD) % MOD;
	}
	while (n) {
		if (n & 1) d = Div(Mul(d, xn), f);
		n >>= 1; xn = Div(Mul(xn, xn), f);
	}
	return d;
}

ll N, K, inv, M;


int main() {
	std::cin >> N >> K >> M;
	/*if (M < N) {
		for (int i = 0; i < N; ++i)
			std::cout << (i == M ? 1 : 0) << '\n';
		return 0;
	}*/
	inv = power(K + 1, MOD - 2);
	Poly A(N, 1), C(N, 0);
	for (int i = 0; i <= K; ++i) C[i] = inv;
	Poly result = kitamasa(C, M);
	// std::cout << result.size() << '\n';
	// for (const int eff : result)
	// 	std::cout << eff << '\n';
	result.resize(N);
	for (int i = 0; i < N; ++i)
		std::cout << result[i] << '\n';
}