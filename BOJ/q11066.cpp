#include <iostream>

#define MAX 1'000'000'000

int cache[500][500], files[500], sum[501];

int dp(int a, int b) {
    if (a == b) return files[a];

    int& result = cache[a][b];
    if (result) return result;

    int cost = sum[b + 1] - sum[a], i;

    for (result = MAX, i = a; i < b; ++i) result = std::min(result, dp(a, i) + dp(i + 1, b) + cost);

    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL); std::cout.tie(NULL);

    int T, K, i, j;
    std::cin >> T;
    while (T--) {
        for (i = 0; i < 500; ++i)
            for (j = 0; j < 500; ++j)
                cache[i][j] = 0;

        std::cin >> K;
        for (i = 0; i < K; ++i) std::cin >> files[i];
        for (sum[0] = 0, i = 1; i <= K; ++i) sum[i] = files[i - 1] + sum[i - 1];

        std::cout << dp(0, K - 1) - sum[K] << '\n';
    }

    return 0;
}