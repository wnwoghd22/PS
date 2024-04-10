#include <stdio.h>
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

int dp[100001];

int main() {
    int N, K, W, V, i, j;
    scanf("%d %d", &N, &K);
    for (i = 1; i <= N; ++i) {
        scanf("%d %d", &W, &V);
        for (j = K; j >= W; --j) dp[j] = MAX(dp[j], dp[j - W] + V);
    }
    printf("%d", dp[K]);
}