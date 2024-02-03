#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long ll;
const int LEN = 3e3;
const ll INF = 1e9;

int N, K;
ll A, B;

struct Pos { 
    ll x, y;
    ll f() const { return A * x + B * y; }
    ll g() const { return x * y; }
    bool operator<(const Pos& o) const { return f() < o.f(); }
} pos[LEN];
ll cross(const Pos& d1, const Pos& d2, const Pos& d3) { return (d2.x - d1.x) * (d3.y - d2.y) - (d2.y - d1.y) * (d3.x - d2.x); }
int ccw(const Pos& d1, const Pos& d2, const Pos& d3) {
    ll c = cross(d1, d2, d3);
    return c > 0 ? 1 : c < 0 ? -1 : 0;
}

Pos g(ll a, ll b) {
    A = a, B = b;
    Pos ret = { 0, 0 };
    std::sort(pos, pos + N);
    for (int i = 0; i < K; ++i) {
        ret.x += pos[i].x;
        ret.y += pos[i].y;
    }
    return ret;
}

Pos min_cost;

void f(const Pos& s, const Pos& e) {
    ll dx = e.x - s.x;
    ll dy = s.y - e.y;
    Pos m = g(dy, dx);
    if (m.g() < min_cost.g()) min_cost = m;
    if (ccw(s, e, m) >= 0) return;
    f(s, m);
    f(m, e);
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::cin >> N >> K;
    for (int i = 0; i < N; ++i) std::cin >> pos[i].x >> pos[i].y;

    std::cout << "check\n";

    Pos s = g(1, 0);
    Pos e = g(0, 1);

    std::cout << "s: " << s.x << ' ' << s.y << '\n';
    std::cout << "e: " << e.x << ' ' << e.y << '\n';

    min_cost = s.g() < e.g() ? s : e;
    f(s, e);
    std::cout << min_cost.g();
}