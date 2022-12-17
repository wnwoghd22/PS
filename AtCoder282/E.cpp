#include <iostream>
#include <queue>
#include <cstring>

typedef long long int ll;
struct Vert {
    ll w, x, y; // weight, x, y
    bool operator()(const Vert& l, const Vert& r) { return l.w < r.w; }
}; 

std::priority_queue<Vert, std::vector<Vert>, Vert> pq;
int N, M, A[500], p[500];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;

    if (p[a] < p[b]) p[a] += p[b], p[b] = a;
    else p[b] += p[a], p[a] = b;

    return true;
}
ll power(ll A, ll B, ll C) {
    if (B == 1) return A % C;
    else {
       ll pw = power(A, B / 2, C);
        return pw * pw % C * (B % 2 ? A : 1) % C;
    }
}

int main() {
    ll result = 0;
    memset(p, -1, sizeof p);
    std::cin >> N >> M;
    for (int i = 0; i < N; ++i) std::cin >> A[i];
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            int w = (power(A[i], A[j], M) + power(A[j], A[i], M)) % M;
            std::cout << i << ' ' << j << ' ' << w << '\n';
            pq.push({ w, i, j });
        }
    }
    while (!pq.empty()) {
        Vert v = pq.top(); pq.pop();
        std::cout << v.x << ' ' << v.y << ' ' << v.w << '\n';
        if (join(v.x, v.y)) result += v.w;
    }
    std::cout << result;
}