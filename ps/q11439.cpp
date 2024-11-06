#include <iostream>

const int LEN = 4e6 + 1;
int N, K, M, f[LEN], c[LEN];

int main() {
	std::cin >> N >> K >> M;

    for (int i = 2; i <= N; ++i) if (!f[i]) { for (int j = i * 2; j <= N; j += i) f[j] = i; f[i] = i; }
    for (int i = 2, k; i <= N; ++i) {
        k = i; while (k > 1) c[f[k]]++, k /= f[k];
    }
    for (int i = 0, k; i < K; ++i) {
        k = i + 1; while (k > 1) c[f[k]]--, k /= f[k];
        k = N - i; while (k > 1) c[f[k]]--, k /= f[k];
    }
    for (int i = 2; i <= N; ++i) {
        std::cout << c[i] << ' ';
    }
}