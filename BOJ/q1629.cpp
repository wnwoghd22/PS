#include <iostream>

#define ll long long int

ll power(ll A, ll B, ll C) {
    if (B == 1) return A % C;
    else {
        ll pw = power(A, B / 2, C);
        return pw * pw % C * (B % 2 ? A : 1) % C;
    }
}

int main() {
    ll A, B, C;
    std::cin >> A >> B >> C;
    std::cout << power(A, B, C);
}