#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int LEN = 1024;
int N, M, t[LEN << 1][LEN << 1];

void init() {
    for (int i = N; i < (N << 1); ++i)
        for (int j = N - 1; j > 0; --j)
            t[i][j] = t[i][j << 1] + t[i][j << 1 | 1];

    for (int i = N - 1; i > 0; --i) {
        for (int j = 1; j < (N << 1); ++j)
            t[i][j] = t[i << 1][j] + t[i << 1 | 1][j];
        // for (int j = N - 1; j > 0; --j)
        //     t[i][j] = t[i][j << 1] + t[i][j << 1 | 1];
    }
}

void update(const int x, const int y, const int c) {
    int i = x, j = y;
    for (t[i += N][j += N] = c; j > 1; j >>= 1)
        t[i][j >> 1] = t[i][j] + t[i][j ^ 1];
    
    for (i; i > 1; i >>= 1) {
        j = y + N;
        t[i >> 1][j] = t[i][j] + t[i ^ 1][j];
        for (; j > 1; j >>= 1)
            t[i >> 1][j >> 1] = t[i >> 1][j] + t[i >> 1][j ^ 1];
    }
}

// [x1, x2) * [y1, y2)
int query(const int x1, const int y1, const int x2, const int y2) {
    int ans = 0, l, r, u = x1, d = x2;
    for (u += N, d += N; u < d; u >>= 1, d >>= 1) {
        if (u & 1) {
            for (l = y1 + N, r = y2 + N; l < r; l >>= 1, r >>= 1) {
                if (l & 1) ans += t[u][l++];
                if (r & 1) ans += t[u][--r];
            }
            ++u;
        }
        if (d & 1) {
            --d;
            for (l = y1 + N, r = y2 + N; l < r; l >>= 1, r >>= 1) {
                if (l & 1) ans += t[d][l++];
                if (r & 1) ans += t[d][--r];
            }
        }
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    std::cin >> N >> M;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            std::cin >> t[i + N][j + N];
    init();
    for (int i = 0, w, x1, x2, y1, y2, c; i < M; ++i) {
        std::cin >> w;
        if (w) {
            std::cin >> x1 >> y1 >> x2 >> y2;
            std::cout << query(--x1, --y1, x2, y2) << '\n';
        }
        else {
            std::cin >> x1 >> y1 >> c;
            update(--x1, --y1, c);
        }
    }
}