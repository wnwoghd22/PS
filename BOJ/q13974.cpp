#include <iostream>

const int INF = 1e9;
const int LEN = 5001;
int dp[LEN][LEN], A[LEN][LEN], files[LEN], sum[LEN];

int main() {
    int T, K, i, j, k, min;
    std::cin >> T;
    while (T--) {
        std::cin >> K;
        for (i = 1; i <= K; ++i) std::cin >> files[i], sum[i] = sum[i - 1] + files[i], A[i][i] = i;
        for (i = 1; i <= K; ++i) {
            for (j = 1; j <= K - i; ++j) {
                dp[j][j + i] = INF;
                for (k = A[j][j + i - 1]; k <= A[j + 1][j + i]; ++k) {
                    min = dp[j][k] + dp[k + 1][j + i] + sum[j + i] - sum[j - 1];
                    if (min < dp[j][j + i]) {
                        dp[j][j + i] = min;
                        A[j][j + i] = k;
                    }
                }
            }
        }
        std::cout << dp[1][K] << '\n';
    }
    return 0;
}