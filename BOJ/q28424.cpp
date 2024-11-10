#include <iostream>
#include <cstring>

const int LEN = 100'002;
int N, Q, m[LEN], c[LEN], p[LEN];

int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return 0;
    if (a > b) p[a] += p[b], p[b] = a;
    else p[b] += p[a], p[a] = b;
    return 1;
}

int main() {
    memset(p, -1, sizeof p);
    std::cin >> N >> Q;
    for (int i = 1; i <= N; ++i) std::cin >> m[i];
    for (int k = 0, q, x, y, i; k < Q; ++k) {
        std::cin >> q >> i;
        if (q == 1) {
            std::cin >> x;
            while (x && i <= N) {
                i = find(i);
                if (i > N) break;
                y = std::min(m[i] - c[i], x);
                x -= y;
                c[i] += y;
                if (c[i] >= m[i]) join(i, i + 1);
                ++i;
            }
        }
        if (q == 2) std::cout << c[i] << '\n';
    }
}