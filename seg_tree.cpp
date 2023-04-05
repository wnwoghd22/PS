// Based from http://codeforces.com/blog/entry/18051
#include <stdio.h>
#define MAX_N 10000

int n;
int t[MAX_N * 2];

void init() {
    for (int i = n - 1; i > 0; --i) {
        t[i] = t[i << 1] + t[i << 1 | 1];
    }
}

// [l, r)
int query(int l, int r) {
    int ans = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ans += t[l++];
        if (r & 1) ans += t[--r];
    }
    return ans;
}

void update(int pos, int val) {
    t[pos + n] = val; // update
    for (pos += n; pos > 1; pos >>= 1) {
        t[pos >> 1] = t[pos] + t[pos ^ 1]; // update by rule
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &t[n + i]); // a[0] => a[n]
    }
    init();
    update(0, 2); // a[0] = 2
    update(3, 2); // a[3] = 2
    int q = query(1, 3); // [0, 3); sum(a[0], ..., a[2]) == 2
    return 0;
}