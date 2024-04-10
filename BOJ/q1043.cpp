#include <iostream>
#include <vector>
#include <cstring>

int p[10'001];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;

    if (p[a] < p[b]) p[b] = a, p[a] -= p[b];
    else p[a] = b, p[b] -= p[a];

    return true;
}
bool is_union(int a, int b) { return find(a) == find(b); }

int main() {
    int N, M, K;
    memset(p, -1, sizeof p);
    std::cin >> N >> M >> K;
    std::vector<int> A(K);
    for (int i = 0; i < K; ++i) {
        std::cin >> A[i];
        if (i > 0) join(A[i], A[i - 1]);
    }
    std::vector<std::vector<int>> party(M);
    for (int i = 0; i < M; ++i) {
        int J;
        std::cin >> J;
        for (int j = 0; j < J; ++j) {
            int k;
            std::cin >> k;
            party[i].push_back(k);
            if (j > 0) join(party[i][j], party[i][j - 1]);
        }
    }
    N = 0;
    for (std::vector<int> p : party) {
        if (K > 0 && is_union(A[0], p[0])) continue;
        N++;
    }
    std::cout << N;
}