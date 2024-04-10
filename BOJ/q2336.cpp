#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int LEN = 500'001;
const int INF = 1e9;
int seg_tree[LEN * 4];
int N, idx, A[LEN], B[LEN], C[LEN];

void update(int n, int x, int s = 0, int e = N - 1, int i = 1) {
    if (n < s || e < n) return;
    if (s == e) {
        seg_tree[i] = x;
        return;
    }
    int m = (s + e) >> 1;
    update(n, x, s, m, i << 1);
    update(n, x, m + 1, e, i << 1 | 1);
    seg_tree[i] = std::min(seg_tree[i << 1], seg_tree[i << 1 | 1]);
}
int get_min(int l, int r, int s = 0, int e = N - 1, int i = 1) {
    if (r < s || e < l) return INF;
    if (l <= s && e <= r) return seg_tree[i];
    int m = (s + e) >> 1;
    return std::min(get_min(l, r, s, m, i << 1), get_min(l, r, m + 1, e, i << 1 | 1));
}

int main() {
    freopen("input.txt", "r", stdin);
    std::cin >> N;
    for (int i = 0; i < N; ++i) std::cin >> A[i];
    for (int i = 0; i < N; ++i) std::cin >> idx, B[idx] = i;
    for (int i = 0; i < N; ++i) std::cin >> idx, C[idx] = i;
    for (int i = 0; i < N * 4; ++i) seg_tree[i] = INF;

    int result = 0;
    for (int i = 0; i < N; ++i) {
        if (get_min(0, B[A[i]] - 1) > C[A[i]]) ++result;
        update(B[A[i]], C[A[i]]);
    }
    std::cout << result;
}