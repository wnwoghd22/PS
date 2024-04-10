#include <iostream>

typedef long long int ll;
const int LEN = 1'000'001;
char s[LEN];
ll lps[LEN], dp[LEN];
int N;

int main() {
    ll result = 0, j = 0;
    std::cin >> N >> s;
    for (int i = 1; i < N; ++i) {
        while (j > 0 && s[i] != s[j]) j = lps[j - 1];
        if (s[i] == s[j]) lps[i] = ++j;
        if (lps[i]) {
            int len = i - lps[i] + 1;
            dp[i] = len + dp[i - len];
            result += dp[i];
        }
    }
    std::cout << result;
}