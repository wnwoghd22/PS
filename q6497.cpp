#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

typedef long long int ll;
typedef std::pair<int, int> pii;
typedef std::pair<ll, pii> CAB;
const int LEN = 200'001;
int p[LEN];
std::priority_queue<CAB, std::vector<CAB>, std::greater<CAB>> pq;

int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;

    if (p[a] < p[b]) p[b] = a, p[a] -= p[b];
    else p[a] = b, p[b] -= p[a];

    return true;
}

ll kruskal() {
    ll result = 0;

    while (!pq.empty()) {
        int A = pq.top().second.first, B = pq.top().second.second;
        ll C = pq.top().first;
        pq.pop();
        if (join(A, B)) result += C;
    }
    return result;
}

void solve(int m, int n) {
    ll total = 0, x, y, z;
    memset(p, -1, sizeof p);
    while (n--) {
        std::cin >> x >> y >> z;
        total += z;
        pq.push({ z, {x, y} });
    }
    std::cout << total - kruskal() << '\n';
}

int main() {
    int N, M;
    std::cin >> M >> N;
    while (M || N) {
        solve(M, N);
        std::cin >> M >> N;
    }
}