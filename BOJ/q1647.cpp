#include <iostream>
#include <queue>
#include <cstring>

typedef std::pair<int, std::pair<int, int>> CAB;

int p[100'001];
std::priority_queue<CAB, std::vector<CAB>, std::greater<CAB>> pq;

int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }

bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;

    if (p[a] < p[b]) p[a] += p[b], p[b] = a;
    else p[b] += p[a], p[a] = b;

    return true;
}

int kruskal(int V) {
    int result = 0; int max = -1;
    memset(p, -1, sizeof p);

    while (V > 1) {
        int A = pq.top().second.first, B = pq.top().second.second, C = pq.top().first;
        pq.pop();
        if (join(A, B)) result += C, --V, max = std::max(max, C);
    }
    return result - max;
}

int main() {
    int V, E, a, b, c;
    std::cin.tie(0)->sync_with_stdio(0);

    std::cin >> V >> E;
    while (E--) {
        std::cin >> a >> b >> c;
        pq.push({ c, {a, b} });
    }
    std::cout << kruskal(V);
}