#include <iostream>
#include <algorithm>
#include <vector>

const int LEN = 500'001;
int N, A, B, arr[LEN], dp[LEN], lis[LEN], len = 0, i, j;
std::vector<int> S;
std::vector<int> result;

int main() {
    std::cin >> N;

    for (i = 0; i < N; ++i) {
        std::cin >> A >> B;
        arr[B] = A;
    }

    for (i = 0; i < LEN; ++i) {
        if (!arr[i]) continue;

        auto pos = std::lower_bound(dp, dp + len, arr[i]);
        *pos = arr[i];
        lis[i] = pos - dp + 1;

        if (pos == dp + len) len++;
    }

    std::cout << N - len << '\n';

    for (j = len, i = LEN - 1; i >= 0; --i)
        if (arr[i] && lis[i] == j && (S.empty() || arr[i] < S.back()))
            S.push_back(arr[i]), arr[i] = 0, --j;
    for (const int& e : arr) if (e) result.push_back(e);
    std::sort(result.begin(), result.end());
    for (const int& e : result) std::cout << e << '\n';
}