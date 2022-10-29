#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
struct pos {
    ll x, y, rx, ry;
    pos(ll x = 0, ll y = 0) : x(x), y(y), rx(1), ry(0) {}
    bool operator<(pos& l) {
        if (rx * l.ry ^ l.rx * ry) return rx * l.ry > l.rx * ry;
        return y < l.y ? true : (y == l.y && x < l.x);
    }
};
ll inline ccw(const pos& p1, const pos& p2, const pos& p3) {
    ll result = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
    return result > 0 ? 1 : result < 0 ? -1 : 0;
}
bool inline disjoint(ll a, ll b, ll c, ll d) { return std::max(a, b) < std::min(c, d) || std::min(a, b) > std::max(c, d); }

int N, M;
std::vector<pos> A, B, Ha, Hb;
void get_convex_hull(std::vector<pos>& p, std::vector<pos>& h) {
    std::sort(p.begin(), p.end());
    for (int i = 1; i < p.size(); ++i) {
        p[i].rx = p[i].x - p[0].x;
        p[i].ry = p[i].y - p[0].y;
    }
    std::sort(p.begin() + 1, p.end());

    for (int i = 0; i < p.size(); ++i) {
        while (h.size() >= 2 && ccw(h[h.size() - 2], h.back(), p[i]) <= 0) h.pop_back();
        h.push_back(p[i]);
    }
}

bool is_inside(const pos& p, const std::vector<pos>& h) {
    ll s = ccw(h[0], h[1], p);
    for (int i = 1; i < h.size(); ++i)
        if (s * ccw(h[i], h[(i + 1) % h.size()], p) <= 0) return false;
    return true;
}
bool is_inside(const std::vector<pos>& a, const std::vector<pos>& b) {
    if (b.size() > 2) for (const pos& p : a) if (is_inside(p, b)) return true;
    return false;
}
bool collide(const pos& a, const pos& b, const pos& c, const pos& d) {
    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);
    if (ab == 0 && cd == 0)
        return !disjoint(a.x, b.x, c.x, d.x) && !disjoint(a.y, b.y, c.y, d.y);
    return ab <= 0 && cd <= 0;
}
bool is_overlap(const std::vector<pos>& a, const std::vector<pos>& b) {
    int n = a.size(), m = b.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (collide(a[i], a[(i + 1) % n], b[j], b[(j + 1) % m]))
                return true;
    return false;
}

void solve() {
    A.clear(), B.clear(), Ha.clear(), Hb.clear();

    bool flag = true;
    std::cin >> N >> M;
    for (ll x, y, i = 0; i < N; ++i) {
        std::cin >> x >> y;
        A.push_back(pos(x, y));
    }
    for (ll x, y, i = 0; i < M; ++i) {
        std::cin >> x >> y;
        B.push_back(pos(x, y));
    }
    get_convex_hull(A, Ha);
    get_convex_hull(B, Hb);

    if (is_inside(Ha, Hb) || 
        is_inside(Hb, Ha) ||
        is_overlap(Ha, Hb)) 
        std::cout << "NO\n";
    else std::cout << "YES\n";
}

int main() {
    int T;
    std::cin >> T;
    while (T--) solve();
}