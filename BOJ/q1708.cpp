#include <iostream>
#include <stack>
#include <algorithm>

typedef long long int ll;
const int LEN = 100'001;

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
pos P[LEN];
int N;
std::stack<int> S;

int main() {
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

    S.push(0), S.push(1);
    for (int k = 2; k < N; ++k) {
        while (S.size() > 1) {
            int p2 = S.top(); S.pop();
            int p1 = S.top();
            if (ccw(P[p1], P[p2], P[k])) {
                S.push(p2);
                break;
            }
        }
        S.push(k);
    }
    std::cout << S.size();
}