#include <iostream>

typedef long long int ll;
const int MOD = 100000;
int N, a, b, c;
ll result = 0;

void balParenthesis(int n, int open, ll score) {
    if ((n & 1) && !open) return;

    if (n == 0) {
        if (open == 0) {
            result = std::max(result, score);
        }
        return;
    }

    if (open > n) return;

    balParenthesis(n - 1, open + 1, (score + b) % MOD);
    if (open > 0) balParenthesis(n - 1, open - 1, score * c % MOD);
}

int main() {
    std::cin >> N >> a >> b >> c;

    balParenthesis(N * 2, 0, a);

    std::cout << result;

    return 0;
}