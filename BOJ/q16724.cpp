#include <iostream>
#include <cstring>

const int LEN = 1'000'000;

int N, M, r, p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;

    if (p[a] < p[b]) p[a] += p[b], p[b] = a;
    else p[b] += p[a], p[a] = b;

    return true;
}

int main() {
    memset(p, -1, sizeof p);
    std::cin >> N >> M;
    char c;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cin >> c;
            join(i * M + j,
                c == 'R' ? i * M + j + 1 :
                c == 'L' ? i * M + j - 1 :
                c == 'U' ? (i - 1) * M + j :
                (i + 1) * M + j
            );
        }
    }
    for (int i = 0; i < N * M; ++i) if (i == find(i)) ++r;
    std::cout << r;
}