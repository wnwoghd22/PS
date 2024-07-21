#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long ll;
const int LEN = 1e5 + 1;
int N, A[LEN], t[LEN];
struct E {
    int a, i;
    bool operator<(const E& o) const { return a < o.a; }
} e[LEN];

ll sum(int i) {
    ll ret = 0;
    while (i > 0) {
        ret += t[i];
        i -= i & -i;
    }
    return ret;
}
void update(int i, ll d) {
    while (i <= N) {
        t[i] += d;
        i += i & -i;
    }
}
bool f[LEN];

ll solve() {
    ll ret = 0;
    memset(t, 0, sizeof t);
    memset(f, 0, sizeof f);
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        std::cin >> e[i].a;
        e[i].i = i;
    }
    std::sort(e, e + N);
    A[e[0].i] = 1;
    for (int i = 1, j = 1; i < N; ++i) {
        if (e[i].a != e[i - 1].a) ++j;
        A[e[i].i] = j;
    }
    for (int i = 0; i < N; ++i) { // preprocess
        if (A[0] > A[i]) {
            std::swap(A[0], A[i]);
            ret++;
        }
    }
    update(A[0], 1);
    f[A[0]] = 1;
    for (int i = 1; i < N; ++i) {
        ret += sum(A[i] - 1);
        if (!f[A[i]]) {
            f[A[i]] = 1;
            update(A[i], 1);
        }
    }
    return ret;
}

int main() {
    int T;
    std::cin >> T;
    while (T--) std::cout << solve() << '\n';
}
