#include <iostream>

const int INF = 1e9;
const int LEN = 501;
int dp[LEN][LEN], files[LEN], sum[LEN];

int main() {
    int T, K, i, j, k;
    std::cin >> T;
    while (T--) {
        std::cin >> K;
        for (i = 1; i <= K; ++i) std::cin >> files[i], sum[i] = sum[i - 1] + files[i];
        for (i = 1; i <= K; ++i) {
            for (j = 1; j <= K - i; ++j) {
                dp[j][j + i] = INF;
                for (k = j; k < j + i; ++k) {
                    dp[j][j + i] = std::min(dp[j][j + i], dp[j][k] + dp[k + 1][j + i] + sum[j + i] - sum[j - 1]);
                }
            }
        }
        std::cout << dp[1][K] << '\n';
    }
    return 0;
}