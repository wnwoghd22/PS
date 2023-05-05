#include <iostream>
#include <vector>

typedef long long ll;
typedef std::vector<ll> Poly;

Poly Mul(const Poly& a, const Poly& b) {
	Poly result(a.size() + b.size() - 1);
	for (int i = 0; i < a.size(); ++i)
		for (int j = 0; j < b.size(); ++j)
			result[i + j] = result[i + j] + a[i] * b[j];
	return result;
}
Poly Div(const Poly& a, const Poly& b) {
	Poly result(a.begin(), a.end());
	for (int i = a.size() - 1; i >= b.size() - 1; --i)
		for (int j = 0; j < b.size(); ++j)
			result[i - b.size() + j + 1] -= result[i] * b[j];
	result.resize(b.size() - 1);
	return result;
}

ll kitamasa(Poly c, Poly a, ll n) {
	Poly d = { 1 }; // result
	Poly xn = { 0, 1 }; // xn = x^1, x^2, x^4, ...
	Poly f(c.size() + 1); f.back() = 1;
	for (int i = 0; i < c.size(); ++i) f[i] = -c[i]; // f(x) = x^k - \sum c_i x^i
	while (n) {
		if (n & 1) d = Div(Mul(d, xn), f);
		n >>= 1; xn = Div(Mul(xn, xn), f);
	}
	ll result = 0;
	for (int i = 0; i < a.size(); ++i) result += d[i] * a[i];
	return result;
}