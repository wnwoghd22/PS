#include <iostream>

typedef long long ll;
const int LEN = 4e6 + 1;
int N, K, M, f[LEN], c[LEN];

ll pow(ll a, ll b, ll m) {
    ll ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % m;
        a = a * a % m; b >>= 1;
    }
    return ret;
}

int main() {
	std::cin >> N >> K >> M;

    for (int i = 2; i <= N; ++i) if (!f[i]) { for (int j = i * 2; j <= N; j += i) f[j] = i; f[i] = i; }
    for (int i = 0, k; i < K; ++i) {
        k = N - i; while (k > 1) c[f[k]]++, k /= f[k];
        k = i + 1; while (k > 1) c[f[k]]--, k /= f[k];
    }
    ll ret = 1;
    for (int i = 2; i <= N; ++i) ret = ret * pow(i, c[i], M) % M;
    std::cout << ret;
}