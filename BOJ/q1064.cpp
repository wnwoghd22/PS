#include <iostream>

typedef long long ll;
typedef long double ld;

struct Pos { int x, y; } a, b, c;
ll cross(const Pos& p1, const Pos& p2, const Pos& p3) { return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x); }
ld euc(const Pos& p1, const Pos& p2) { 
    ld dx = p1.x - p2.x, dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    if (!cross(a, b, c)) std::cout << -1;
    else {
        std::cout << std::fixed;
        std::cout.precision(10);
        ld ab = euc(a, b);
        ld bc = euc(b, c);
        ld ac = euc(a, c);
        ld min = std::min({ ab, bc, ac });
        ld max = std::max({ ab, bc, ac });
        std::cout << (max - min) * 2;
    }
}