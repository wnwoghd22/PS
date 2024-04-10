#include <iostream>
#include <cstring>

const int LEN = 200'001;
int A[LEN], AP[LEN], AQ[LEN];

namespace P {
    int p[LEN];
    int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;

        if (a < b) p[a] += p[b], p[b] = a;
        else p[b] += p[a], p[a] = b;

        return true;
    }
}
namespace Q {
    int p[LEN];
    int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;

        if (a < b) p[a] += p[b], p[b] = a;
        else p[b] += p[a], p[a] = b;

        return true;
    }
}

void solve() {
    memset(P::p, -1, sizeof P::p);
    memset(Q::p, -1, sizeof Q::p);
    memset(AP, -1, sizeof AP);
    memset(AQ, -1, sizeof AQ);
    int N; bool flag = true;
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
        if (P::find(A[i]) == A[i]) {
            AP[i] = A[i];
            P::join(A[i] - 1, A[i]);
        }
        else if (Q::find(A[i]) == A[i]) {
            AQ[i] = A[i];
            Q::join(A[i] - 1, A[i]);
        }
        else flag = false;
    }
    if (!flag) {
        std::cout << "NO\n";
        return;
    }
    for (int i = 0; i < N; ++i) {
        if (~AP[i]) {
            int k = Q::find(AP[i]);
            if (k) {
                AQ[i] = k;
                Q::join(k - 1, k);
            }
            else {
                std::cout << "NO\n";
                return;
            }
        }
        else {
            int k = P::find(AQ[i]);
            if (k) {
                AP[i] = k;
                P::join(k - 1, k);
            }
            else {
                std::cout << "NO\n";
                return;
            }
        }
    }
    std::cout << "YES\n";
    for (int i = 0; i < N; ++i)
        std::cout << AP[i] << ' ';
    std::cout << '\n';
    for (int i = 0; i < N; ++i)
        std::cout << AQ[i] << ' ';
    std::cout << '\n';
}
int main() {
    int T;
    std::cin >> T;
    while (T--) solve();
}