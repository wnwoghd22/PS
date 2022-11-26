#include <iostream>
#include <map>
#include <cstring>

const int LEN = 2000;

std::map<std::string, int> M;

int N, i, p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;

    if (p[a] < p[b]) p[a] += p[b], p[b] = a;
    else p[b] += p[a], p[a] = b;

    return true;
}

int main() {
    M["ChongChong"] = 0;
    memset(p, -1, sizeof p);
    std::cin >> N;
    std::string s;
    int a, b;

    while (N--) {
        std::cin >> s;
        if (M.find(s) == M.end()) M[s] = ++i;
        a = M[s];

        std::cin >> s;
        if (M.find(s) == M.end()) M[s] = ++i;
        b = M[s];

        if (find(a) == find(0) || find(b) == find(0)) join(a, b);
    }
    std::cout << -p[find(0)];
}