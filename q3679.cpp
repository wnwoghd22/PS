#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
struct pos {
    ll i, x, y, rx, ry;
    pos(ll i = 0, ll x = 0, ll y = 0) : i(i), x(x), y(y), rx(1), ry(0) {}
    bool operator<(pos& l) {
        if (rx * l.ry ^ l.rx * ry) return rx * l.ry > l.rx * ry;
        return y < l.y ? true : (y == l.y && x < l.x);
    }
};
ll inline ccw(const pos& p1, const pos& p2, const pos& p3) {
    ll result = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
    return result > 0 ? 1 : result < 0 ? -1 : 0;
}

int N, M;
std::vector<pos> P;

void solve() {
    P.clear();

    std::cin >> N;
    for (ll x, y, i = 0; i < N; ++i) {
        std::cin >> x >> y;
        P.push_back(pos(i, x, y));
    }
    std::sort(P.begin(), P.end());
    for (int i = 1; i < P.size(); ++i) {
        P[i].rx = P[i].x - P[0].x;
        P[i].ry = P[i].y - P[0].y;
    }
    std::sort(P.begin() + 1, P.end());
    for (M = N - 1; !ccw(P[0], P[M], P[M - 1]); --M);

    for (int i = 0; i < M; ++i) std::cout << P[i].i << ' ';
    for (int i = N - 1; i >= M; --i) std::cout << P[i].i << ' ';
    std::cout << '\n';
}

int main() {
    int T;
    std::cin >> T;
    while (T--) solve();
}