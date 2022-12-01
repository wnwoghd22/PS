#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>

typedef std::complex<double> cd;
const int LEN = 200'001;

void fft(std::vector<cd>& v) {
    int size = v.size();
    if (size == 1) return;

    std::vector<cd> v1(size / 2), v2(size / 2);
    for (int i = 0; i * 2 < size; ++i) {
        v1[i] = v[i * 2];
        v2[i] = v[i * 2 + 1];
    }
    fft(v1);
    fft(v2);

    double x = 2 * M_PI / size;
    cd W(1), Wn(cos(x), sin(x));

    for (int i = 0; i * 2 < size; ++i, W *= Wn) {
        v[i] = v1[i] + W * v2[i];
        v[i + size / 2] = v1[i] - W * v2[i];
    }
}
void ifft(std::vector<cd>& v) {
    int size = v.size();
    if (size == 1) return;

    std::vector<cd> v1(size / 2), v2(size / 2);
    for (int i = 0; i * 2 < size; ++i) {
        v1[i] = v[i * 2];
        v2[i] = v[i * 2 + 1];
    }
    ifft(v1);
    ifft(v2);

    double x = -2 * M_PI / size;
    cd W(1), Wn(cos(x), sin(x));

    for (int i = 0; i * 2 < size; ++i, W *= Wn) {
        v[i] = v1[i] + W * v2[i];
        v[i + size / 2] = v1[i] - W * v2[i];
    }
    for (cd& e : v) e /= 2;
}

std::vector<int> multiply(std::vector<int>& a, std::vector<int>& b) {
    std::vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa); fft(fb);

    for (int i = 0; i < n; ++i) fa[i] *= fb[i];

    ifft(fa);

    std::vector<int> result(n);
    for (int i = 0; i < n; ++i) {
        result[i] = round(fa[i].real());
    }
    return result;
}

int main() {
    int n, m, k, d, count = 0;
    std::vector<int> A(LEN, 0);

    std::cin >> n;
    while (n--) {
        std::cin >> k;
        A[k] = 1;
    }
    std::vector<int> result = multiply(A, A);

    std::cin >> m;
    while (m--) {
        std::cin >> d;
        count += (A[d] || result[d]);
    }
    std::cout << count;
}