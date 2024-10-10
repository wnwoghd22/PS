#include "aliens.h"
#include <algorithm>
#include <iostream>

typedef long long ll;
typedef long double ld;
const int LEN = 500'001;
const ld ERR = 1e-7;
const ll INF = 1e17;

struct Pos {
    int r, c;
    bool operator<(const Pos& p) const { return r == p.r ? c < p.c : r < p.r; }
} pool[LEN], pos[LEN];

int N;

ll dp[LEN], C[LEN];
struct Line {
    ll a, b;
    ld x;
    int i;
    Line() : a(0), b(0), x(-INF), i(0) {}
    Line(ll a, ll b, ld x, int i) : a(a), b(b), x(x), i(i) {}
    ld operator&(const Line& r) { return (ld)(r.b - b) / (a - r.a); } // get pos X of intersect of l and r
    ll f(ll x) { return a * x + b; }
} hull[LEN];
int ptr, _size;

void add_line(Line l) {
    if (!_size) {
        hull[_size++] = l;
        return;
    }
    while (_size > 1 && hull[_size - 1].x > (hull[_size - 1] & l)) --_size;
    l.x = hull[_size - 1] & l;
    hull[_size++] = l;
    if (ptr >= _size) ptr = _size - 1;
}

int f(ll lambda) {
    _size = ptr = 0;
    add_line(Line());
    ll base = pos[0].r;
    for (int i = 0; i < N; ++i) {
        ll r0 = pos[i].r - base, c0 = pos[i].c - base;
        ll r1 = pos[i + 1].r - base, c1 = pos[i + 1].c - base;

        while (ptr < _size - 1 && hull[ptr + 1].x < c0) ++ptr;
        dp[i] = hull[ptr].f(c0) + (c0 + 1) * (c0 + 1) + lambda;
        C[i + 1] = C[hull[ptr].i] + 1;

        ll A = -2 * r1;
        ll B = -2 * r1 + r1 * r1 + dp[i];
        if (r1 <= c0) B -= (c0 - r1 + 1) * (c0 - r1 + 1);
        add_line(Line(A, B, -INF, i + 1));
    }
    return C[N];
}

ll take_photos(int n, int m, int k, std::vector<int> r, std::vector<int> c) {
    for (int i = N = 0; i < n; ++i) {
        if (r[i] < c[i]) pool[i] = { r[i], c[i] };
        else pool[i] = { c[i], r[i] };
    }
    std::sort(pool, pool + n);
    pos[N++] = pool[0];
    for (int i = 1; i < n; ++i) {
        if (pool[i].r == pos[N - 1].r) pos[N - 1].c = pool[i].c;
        else if (pool[i].c > pos[N - 1].c) pos[N++] = pool[i];
    }

    for (int i = 0; i < N; ++i) std::cout << "Pos " << i << ": " << pos[i].r << ' ' << pos[i].c << '\n';

    ll s = 0, e = (ll)m * m, lambda;
    ll lx = INF, ly = 0, rx = -1, ry = 0;
    while (s <= e) {
        lambda = s + e >> 1;
        int cnt = f(lambda);
        if (cnt == k) return dp[N - 1] - lambda * k;
        if (cnt > k) { // too many photos. need to add more cost
            s = lambda + 1;
            if (cnt < lx)
                lx = cnt,
                ly = dp[N - 1] - lambda * cnt;
        }
        else {
            e = lambda - 1;
            if (cnt > rx)
                rx = cnt, 
                ry = dp[N - 1] - lambda * cnt;
        }
    }
    std::cout << "Not trivial\n";
    std::cout << lx << ' ' << ly << ' ' << rx << ' ' << ry << '\n';

    return ry + (ly - ry) / (rx - lx) * (rx - k);
}
