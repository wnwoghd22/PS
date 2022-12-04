#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>

typedef long long int ll;
typedef std::complex<double> cd;
const int LEN = 1'000'001;

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
    // n이 무조건 2^n 이여야 하기 때문에 변환!
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
    int N, T;
    std::vector<ll> A(LEN, 1), B(LEN, 0);
    A[0] = A[1] = 0;
    for (int i = 2; i < LEN; ++i) {
        if (!A[i]) continue;
        for (int j = i * 2; j < LEN; j += i)
            A[j] = 0;
    }
    for (int i = 0; i * 2 < LEN; ++i) {
        if (A[i]) B[i * 2] = 1;
    }

    std::vector<ll> R = multiply(A, B);

    std::cin >> T;
    while (T--) {
        std::cin >> N;
        std::cout << R[N] << '\n';
    }
}