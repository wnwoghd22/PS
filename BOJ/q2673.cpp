#include <iostream>
#include <algorithm>
#include <cstring>

int dp[101][101], A[101];
int N, a, b;

int f(int i, int r) {
    if (i >= r) return 0;
    int& ref = dp[i][r];
    if (~ref) return ref;
    ref = f(i + 1, r);
    if (A[i] && A[i] <= r) ref = std::max(ref, f(i + 1, A[i] - 1) + f(A[i] + 1, r) + 1);
    return ref;
}

int main() {
    memset(dp, -1, sizeof dp);
    std::cin >> N;
    while (N--) {
        std::cin >> a >> b;
        if (a > b) std::swap(a, b);
        A[a] = b;
    }
    std::cout << f(1, 100);
}