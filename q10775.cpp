#include <iostream>
#include <cstring>

const int LEN = 10'001;
int p[LEN];

int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }

bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;

    if (a < b) p[a] += p[b], p[b] = a;
    else p[b] += p[a], p[a] = b;

    return true;
}

int main() {
    memset(p, -1, sizeof p);
    int G, P, D = 0, g;
    std::cin >> G >> P;
    while (P--) {
        std::cin >> g;
        g = find(g);
        if (g) join(g - 1, g);
        else break;
        ++D;
    }
    std::cout << D;
}