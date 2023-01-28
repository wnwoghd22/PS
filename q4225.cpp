#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef long long int ll;
const int LEN = 101;

struct pos {
    ll x, y;
    ll rx, ry; // relative pos
    pos(ll x = 0, ll y = 0) : x(x), y(y), rx(1), ry(0) {}
} P[LEN];
bool comp(const pos& p1, const pos& p2) {
    if (p1.rx * p2.ry ^ p2.rx * p1.ry) return p1.rx * p2.ry > p2.rx * p1.ry;
    return p1.y < p2.y ? true : (p1.y == p2.y && p1.x < p2.x);
}
bool ccw(pos& p1, pos& p2, pos& p3) { return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y > 0; }
double distance(pos& p1, pos& p2, pos& p3) {
    double num = std::abs(p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y);
    double den = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    return num / den;
}

double solve(int N) {
    std::vector<int> S;
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
    double result = 1e20;
    for (int i = 0; i < S.size(); ++i) {
        double current = 0;
        for (int j = (i + 2) % S.size(); j ^ i; j = (j + 1) % S.size()) {
            double dist = distance(P[S[i]], P[S[(i + 1) % S.size()]], P[S[j]]);
            current = std::max(current, dist);
        }
        result = std::min(result, current);
    }
    return result;
}

int main() { 
    int T = 1, N;
    std::cout << std::fixed;
    std::cout.precision(2);
    while (true) {
        std::cin >> N;
        if (!N) break;
        double result = ceil(solve(N) * 100) / 100;
        std::cout << "Case " << T++ << ": " << result << '\n';
    }
}