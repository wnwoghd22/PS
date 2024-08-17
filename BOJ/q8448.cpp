#include <iostream>

typedef long long ll;
const ll INF = 1e12;
const int LEN = 5e5;

int N;
ll pivot[8];
ll p[LEN][3];

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::cin >> N;
    for (int i = 0; i < 8; ++i) pivot[i] = -INF;
    for (int i = 0; i < N; ++i) {
        std::cin >> p[i][0] >> p[i][1] >> p[i][2];
        for (int b = 0; b < 8; ++b) {
            ll cur = 0;
            for (int j = 0; j < 3; ++j) {
                if (b & 1 << j) cur += p[i][j];
                else cur -= p[i][j];
            }
            pivot[b] = std::max(pivot[b], cur);
        }
    }
    for (int i = 0; i < N; ++i) {
        ll ret = 0;
        for (int b = 0; b < 8; ++b) {
            ll cur = pivot[b];
            for (int j = 0; j < 3; ++j) {
                if (~b & 1 << j) cur += p[i][j];
                else cur -= p[i][j];
            }
            ret = std::max(ret, cur);
        }
        std::cout << ret << '\n';
    }
}