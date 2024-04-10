#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>

typedef long long int ll;
typedef std::complex<double> cd;
const int LEN = 300'001;
int s[LEN * 4];

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
    std::string a, b;
    std::cin >> a >> b;
    if (a == "0" || b == "0") {
        std::cout << 0;
        return 0;
    }

    std::vector<int> A(LEN, 0), B(LEN, 0);
    for (int i = 0; i < a.length(); ++i) A[i] = a[a.length() - i - 1] - '0';
    for (int i = 0; i < b.length(); ++i) B[i] = b[b.length() - i - 1] - '0';
    std::vector<int> R = multiply(A, B);

    int temp = 0;
    for (int i = 0; i < R.size(); ++i) {
        temp += R[i];
        s[i] = temp % 10;
        temp /= 10;
    }
    bool flag = false;
    for (int i = LEN * 4 - 1; i >= 0; --i) {
        if (!flag && !s[i]) continue;
        if (!flag && s[i]) flag = true;
        std::cout << s[i];
    }
}