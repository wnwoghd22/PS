#include <iostream>
#include <vector>
#include <complex>

typedef long long ll;
typedef std::vector<ll> Poly;
typedef std::complex<double> cd;
const ll MOD = 1e9 + 7;

ll power(ll a, ll b) {
	ll p = 1;
	while (b) {
		if (b & 1) p = p * a % MOD;
		b >>= 1; a = a * a % MOD;
	}
	return p;
}
void fft(std::vector<cd>& a, bool inv = false) {
	int n = a.size(), j = 0;
	std::vector<cd> roots(n / 2);
	for (int i = 1; i < n; i++) {
		int bit = (n >> 1);
		while (j >= bit) {
			j -= bit;
			bit >>= 1;
		}
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
	for (int i = 0; i < n / 2; i++) {
		roots[i] = cd(cos(ang * i), sin(ang * i));
	}
	for (int i = 2; i <= n; i <<= 1) {
		int step = n / i;
		for (int j = 0; j < n; j += i) {
			for (int k = 0; k < i / 2; k++) {
				cd u = a[j + k], v = a[j + k + i / 2] * roots[step * k];
				a[j + k] = u + v;
				a[j + k + i / 2] = u - v;
			}
		}
	}
	if (inv) for (int i = 0; i < n; i++) a[i] /= n;
}

Poly Mul(const Poly& a, const Poly& b) {
	std::vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 2; while (n < a.size() + b.size()) n <<= 1;
	fa.resize(n); fb.resize(n);
	fft(fa, 0); fft(fb, 0);
	for (int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, 1);
	std::vector<ll> ret(n);
	for (int i = 0; i < n; i++) ret[i] = (ll)round(fa[i].real());
	return ret;
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