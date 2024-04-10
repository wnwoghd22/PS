#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>

typedef std::vector<int> vi;
typedef std::complex<double> base;
const int LEN = 1'000'001;
bool sieve[LEN];

std::vector<int> s, t;
class FFT_mul {
private:
	int n, kk, sn, tn;
	inline int bit_reverse(const int x, int k) {
		int res = 0;
		for (int i = 0; i < k; ++i)
			res ^= ((x >> i) & 1) << (k - i - 1);
		return res;
	}
public:
	FFT_mul() {
		sn = s.size();
		tn = t.size();
		n = 1, kk = 0;
		while (n < sn + tn) n <<= 1, ++kk;
	}
	void fft(std::vector<base>& arr, bool inv) {
		for (int i = 0; i < n; ++i) {
			int j = bit_reverse(i, kk);
			if (i < j) std::swap(arr[i], arr[j]);
		}

		for (int i = 2; i <= n; i <<= 1) {
			double angle = inv ? (-2 * M_PI / i) : (2 * M_PI / i);
			base w = base(cos(angle), sin(angle));
			for (int j = 0; j < n; j += i) {
				base twiddle_factor = base(1, 0);
				for (int k = 0; k < i / 2; ++k) {
					base temp = twiddle_factor * arr[j + k + i / 2];
					arr[j + k + i / 2] = arr[j + k] - temp;
					arr[j + k] = arr[j + k] + temp;
					twiddle_factor *= w;
				}
			}
		}
	}
	vi multiply() {
		vi ret(n + 1, 0);
		std::vector<base> x, y;
		for (int i = 0; i < n; ++i) {
			if (i < sn) x.push_back(base(s[i], 0));
			else x.push_back(base(0, 0));
			if (i < tn) y.push_back(base(t[i], 0));
			else y.push_back(base(0, 0));
		}
		fft(x, true);
		fft(y, true);
		for (int i = 0; i < n; ++i) x[i] = x[i] * y[i];
		fft(x, false);
		for (int i = 0; i < n; ++i) x[i] /= n;
		for (int i = 0; i < n; ++i) ret[i] = (int)round(x[i].real());

		return ret;

	}
};

int main() {
	freopen("input.txt", "r", stdin);
	s.resize(LEN);
	t.resize(LEN);
	for (int i = 2; i < LEN; ++i) {
		if (sieve[i]) continue;
		s[i] = t[i] = 1;
		for (int j = i * 2; j < LEN; j += i) sieve[j] = true;
	}
	FFT_mul fft = FFT_mul();
	vi ans = fft.multiply();
	int T, N, A;
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		A = ans[N];
		if (!sieve[N / 2]) ++A;
		A /= 2;
		std::cout << A << '\n';
	}
}