#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>

typedef std::pair<int, std::pair<double, double>> CAB;
typedef std::pair<double, double> pdd;

int p[10'001];
std::priority_queue<CAB, std::vector<CAB>, std::greater<CAB>> pq;

int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;

    if (p[a] < p[b]) p[b] = a, p[a] -= p[b];
    else p[a] = b, p[b] -= p[a];

    return true;
}

double kruskal(int V) {
    double result = 0;
    memset(p, -1, sizeof p);

    while (V > 1) {
        int A = pq.top().second.first, B = pq.top().second.second;
        int C = pq.top().first;
        pq.pop();
        if (join(A, B)) result += sqrt(C), --V;
    }
    return result;
}
double distance(double x1, double y1, double x2, double y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
    int V, a, b; std::vector<pdd> v;
    double x, y;
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> V;
    for (a = 0; a < V; ++a) std::cin >> x >> y, v.push_back({ x, y });

    for (a = 1; a <= V; ++a) {
        for (b = a + 1; b <= V; ++b) {
            int c = distance(v[a - 1].first, v[a - 1].second, v[b - 1].first, v[b - 1].second);
            pq.push({ c, {a, b} });
        }
    }

    std::cout << kruskal(V);
}