#include <iostream>
#include <stack>

typedef long long int ll;

int main() {
    std::stack<std::pair<ll, ll>> S;
    ll N, a, pair = 0;
    std::cin >> N;
    while (N--) {
        std::cin >> a;
        while (!S.empty() && S.top().first < a) {
            pair += S.top().second + (S.size() == 1);
            S.pop();
        }
        if (!S.empty()) {
            if (S.top().first == a) S.top().second++, pair += S.top().second;
            else S.push({ a, 1 }), ++pair;
        }
        else S.push({ a, 0 });
    }
    std::cout << pair;
}