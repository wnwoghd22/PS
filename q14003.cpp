#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>

int A[1'000'000];
int dp[1'000'000];
int lis[1'000'000];

int main() {
    int N, len = 0, i, j;
    std::stack<int> S;

    std::cin >> N;

    for (i = 0; i < N; ++i) {
        scanf("%d", A + i);

        auto pos = std::lower_bound(dp, dp + len, A[i]);
        *pos = A[i];
        lis[i] = pos - dp + 1;

        if (pos == dp + len) len++;
    }

    std::cout << len << '\n';

    for (j = len, i = N - 1; i >= 0; --i)
        if (lis[i] == j && (S.empty() || A[i] < S.top()))
            S.push(A[i]), --j;

    while (!S.empty()) std::cout << S.top() << ' ', S.pop();
}