#include <iostream>
#include <algorithm>
#include <vector>

const int LEN = 2e5 + 1;
const int INF = 1e9 + 7;

int N, A[LEN];
std::vector<int> V;

int l_len[LEN], r_len[LEN];
int ret, ans[LEN];

void solve() {
    std::cin >> N;
    for (int i = 0; i < N; ++i) std::cin >> A[i];
    V.clear();
    V.push_back(-INF);
    for (int i = 0; i < N; ++i) {
        if (V.back() < A[i]) {
            l_len[i] = V.size();
            V.push_back(A[i]);
        }
        else {
            int idx = std::lower_bound(V.begin(), V.end(), A[i]) - V.begin();
            l_len[i] = idx;
            V[idx] = A[i];
        }
    }
    int L = V.size() - 1;

    V.clear();
    V.push_back(-INF);
    for (int i = N - 1; i >= 0; --i) {
        if (V.back() < -A[i]) {
            r_len[i] = V.size();
            V.push_back(-A[i]);
        }
        else {
            int idx = std::lower_bound(V.begin(), V.end(), -A[i]) - V.begin();
            r_len[i] = idx;
            V[idx] = -A[i];
        }
    }

    std::cout << L << '\n';
    for (int i = 0; i < N; ++i) std::cout << l_len[i] << ' '; std::cout << '\n';
    for (int i = 0; i < N; ++i) std::cout << r_len[i] << ' '; std::cout << '\n';

    ret = 0;
    for (int i = 0; i < N; ++i) {
        if (l_len[i] - 1 + r_len[i] >= L) ans[ret++] = i + 1;
    }
    std::cout << ret << '\n';
    for (int i = 0; i < ret; ++i) std::cout << ans[i] << ' ';
    std::cout << '\n';
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int t;
    std::cin >> t;
    while (t--) solve();
}