#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>

typedef long long ll;
typedef long double ld;
typedef std::complex<ld> cd;
const int LEN = 1'000'001;

const ll P = 99991;
const ll A = 55048, B = 44944, C = 22019;

const int PP = 33330; // pisano period
ll a[PP] = { 1, }, b[PP] = { 1, };

ll pow(ll a, ll b, ll m) {
	ll r = 1;
	while (b) {
		if (b & 1)
			r = r * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return r;
}
ll fibo(ll n) { return (pow(A, n, P) - pow(B, n, P) + P) * C % P; }

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
	ld ang = 2 * acos(-1) / n * (inv ? -1 : 1);
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

std::vector<ll> multiply(std::vector<ll>& v, std::vector<ll>& w) {
	std::vector<cd> fv(v.begin(), v.end()), fw(w.begin(), w.end());
	int n = 2; while (n < v.size() + w.size()) n <<= 1;
	fv.resize(n); fw.resize(n);
	fft(fv, 0); fft(fw, 0);
	for (int i = 0; i < n; i++) fv[i] *= fw[i];
	fft(fv, 1);
	std::vector<ll> ret(n);
	for (int i = 0; i < n; i++) ret[i] = (ll)round(fv[i].real());
	return ret;
}

ll Ak, Bk, E[LEN], arr[LEN];
void f(int l, int r) {
	if (l == r) return;
	int m = l + r >> 1;
	f(l, m); f(m + 1, r);
	std::vector<ll> A, B;
	for (int i = l << 1; i <= (m << 1 | 1); ++i) A.push_back(arr[i]);
	for (int i = m + 1 << 1; i <= (r << 1 | 1); ++i) B.push_back(arr[i]);
	std::vector<ll> v = multiply(A, B);
	for (int i = 0; i <= (r - l << 1 | 1); ++i) arr[(l << 1) + i] = v[i] % P;
}

int N, K;

int main() {
	for (int i = 1; i < PP; ++i) {
		a[i] = a[i - 1] * A % P;
		b[i] = b[i - 1] * B % P;
	}
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) std::cin >> E[i];
	
	for (int i = 0; i < N; ++i) arr[i << 1] = 1, arr[i << 1 | 1] = a[E[i] % PP];
	f(0, N - 1); Ak = arr[K];

	for (int i = 0; i < N; ++i) arr[i << 1] = 1, arr[i << 1 | 1] = b[E[i] % PP];
	f(0, N - 1); Bk = arr[K];

	std::cout << (Ak - Bk + P) * C % P;
}