#include <iostream>

struct Magnet {
    int pol[8];
    int rot = 0;
    int get_12() { return pol[rot]; }
    int get_3() { return pol[(rot + 2) % 8]; }
    int get_9() { return pol[(rot + 6) % 8]; }
    Magnet* l = 0;
    Magnet* r = 0;
    void rotateL(int dir) {
        if (l && get_9() ^ l->get_3()) l->rotateL(dir * -1);
        rot += (dir + 8);
        rot %= 8;
    }
    void rotateR(int dir) {
        if (r && get_3() ^ r->get_9()) r->rotateR(dir * -1);
        rot += (dir + 8);
        rot %= 8;
    }
    void rotate(int dir) {
        if (l && get_9() ^ l->get_3()) l->rotateL(dir * -1);
        if (r && get_3() ^ r->get_9()) r->rotateR(dir * -1);
        rot += (dir + 8);
        rot %= 8;
    }
} *m[4];

int solve() {
    int k, n, d;
    std::cin >> k;
    for (int i = 0; i < 4; ++i) {
        m[i]->rot = 0;
        for (int j = 0; j < 8; ++j) std::cin >> m[i]->pol[j];
    }
    while (k--) {
        std::cin >> n >> d;
        m[n - 1]->rotate(d * -1);
    }
    // std::cout << m[0]->get_12() << ' ' << m[1]->get_12() << ' ' << m[2]->get_12() << ' ' << m[3]->get_12() << '\n';
    return m[0]->get_12() + m[1]->get_12() * 2 + m[2]->get_12() * 4 + m[3]->get_12() * 8;
}

int main() {
    for (int i = 0; i < 4; ++i) m[i] = new Magnet;
    m[0]->r = m[1];
    m[1]->l = m[0]; m[1]->r = m[2];
    m[2]->l = m[1]; m[2]->r = m[3];
    m[3]->l = m[2];

    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}