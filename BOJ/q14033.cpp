#include <iostream>
#include <cstring>

const int INF = 1e9;
int N, M, arr[18][18];
int dp[18][1 << 18];

int dfs(int x, int visited) {
    if (x == N - 1) return 0;

    int& ref = dp[x][visited];
    if (~ref) return ref;

    ref = -INF;
    for (int i = 1; i < N; ++i) {
        if (visited & (1 << i)) continue;
        if (!arr[x][i]) continue;

        ref = std::max(ref, dfs(i, visited | (1 << i)) + arr[x][i]);
    }
    
    return ref;
}

int main() {
    std::cin >> N >> M;
    
    for (int i = 0, s, d, l; i < M; ++i) {
        std::cin >> s >> d >> l;
        arr[s][d] = l;
    }

    memset(dp, -1, sizeof dp);
    std::cout << dfs(0, 1);
}