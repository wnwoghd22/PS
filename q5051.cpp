#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>

typedef long long ll;
typedef std::complex<double> cd;
const int LEN = 500'001;

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
int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	int N;
	ll result = 0;
	std::cin >> N;
	std::vector<ll> A(N, 0), B(N, 0);
	for (ll i = 1; i < N; ++i) A[(i * i) % N]++;
	
	std::vector<ll> R = multiply(A, A);
	for (int i = 0; i < N << 1; ++i) B[i % N] += R[i];
	for (int i = 0; i < N; ++i) B[(i << 1) % N] += A[i];
	for (int i = 0; i < N; ++i) {
		std::cout << B[i] << ' ' << A[i] << '\n';
		result += (B[i] >> 1) * A[i];
	}
	std::cout << result;
}