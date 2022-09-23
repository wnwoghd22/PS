#include <iostream>
#include <stack>

int main() {
    std::stack<std::pair<int, int>> S;
    int N, a, pair = 0;
    std::cin >> N;
    while (N--) {
        std::cin >> a;
        while (!S.empty() && S.top().first < a) {
            pair += S.top().second;
            S.pop();
        }
        if (!S.empty()) {
            if (S.top().first == a) {
                if (S.size() == 1) pair += S.top().second, S.top().second++;
                else S.top().second++, pair += S.top().second;
            }
            else pair++, S.push({ a, 1 });
        }
        else S.push({ a, 1 });
    }
    std::cout << pair;
}