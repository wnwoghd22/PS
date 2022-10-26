#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
const int LEN = 200'001;

struct pos {
    ll x, y;
    ll rx, ry; // relative pos
    pos(ll x = 0, ll y = 0) : x(x), y(y), rx(1), ry(0) {}
};
bool comp(const pos& p1, const pos& p2) {
    if (p1.rx * p2.ry ^ p2.rx * p1.ry) return p1.rx * p2.ry > p2.rx * p1.ry;
    return p1.y < p2.y ? true : (p1.y == p2.y && p1.x < p2.x);
}
bool ccw(pos& p1, pos& p2, pos& p3) { return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y > 0; }
ll ccw(pos& p1, pos& p2, pos& p3, pos& p4) {
    ll lx = p2.x - p1.x, ly = p2.y - p1.y, rx = p4.x - p3.x, ry = p4.y - p3.y;
    return lx * ry - rx * ly;
}
//bool ccw(pos& p1, pos& p2, pos& p3, pos& p4) {
//    pos pp(p4.x - p3.x + p2.x, p4.y - p3.y + p2.y);
//    return ccw(p1, p2, pp);
//}
ll distance(pos& p1, pos& p2) { return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y); }

pos P[LEN];
int N;
std::vector<int> S;

void rotating_calipers(std::vector<int>& c) {
    int l = 0, r = 1, n = c.size(), ans1, ans2;
    /* for (int i = 1; i < n; ++i) {
        if (P[convex[i]].x < P[convex[l]].x) l = i;
        if (P[convex[i]].x > P[convex[r]].x) r = i;
    } */
    ans1 = c[l], ans2 = c[r];
    ll max = distance(P[c[l]], P[c[r]]);
    for (int i = 0; i < n * 2; ++i) {
        ll cross = ccw(P[c[l]], P[c[(l + 1) % n]], P[c[(r + 1) % n]], P[c[r]]);

        if (cross > 0) l = (l + 1) % n;
        if (cross < 0) r = (r + 1) % n;
        if (!cross) l = (l + 1) % n, r = (r + 1) % n;

        ll d = distance(P[c[l]], P[c[r]]);
        if (d > max) {
            max = d;
            ans1 = c[l], ans2 = c[r];
        }
    }
    std::cout << P[ans1].x << ' ' << P[ans1].y << ' ' << P[ans2].x << ' ' << P[ans2].y << '\n';
}

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        S.clear();

        std::cin >> N;
        for (ll x, y, i = 0; i < N; ++i) {
            std::cin >> x >> y;
            P[i] = pos(x, y);
        }

        std::sort(P, P + N, comp);
        for (int i = 1; i < N; ++i) {
            P[i].rx = P[i].x - P[0].x;
            P[i].ry = P[i].y - P[0].y;
        }
        std::sort(P + 1, P + N, comp);

        S.push_back(0), S.push_back(1);
        for (int k = 2; k < N; ++k) {
            while (S.size() > 1) {
                int p2 = S.back(); S.pop_back();
                int p1 = S.back();
                if (ccw(P[p1], P[p2], P[k])) {
                    S.push_back(p2);
                    break;
                }
            }
            S.push_back(k);
        }
        rotating_calipers(S);
    }
}