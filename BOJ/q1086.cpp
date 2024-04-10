#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long int ll;

ll N, K, arr[15], numlen[15], p[51];
std::string s[15];
ll dp[101][1 << 15];

ll gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

ll dfs(ll current, ll visited) {
    if (visited == (1 << N) - 1) return !current;

    ll& ref = dp[current][visited];
    if (ref != -1) return ref;

    ref = 0;
    for (int i = 0; i < N; ++i) {
        if (visited & (1 << i)) continue;

        ll remain = (current * p[numlen[i]] + arr[i]) % K;

        ref += dfs(remain, visited | (1 << i));
    }
    return ref;
}

int main() {
    ll f = 1, i;
    std::cin >> N;
    for (i = 2; i <= N; ++i) f *= i;

    for (i = 0; i < N; ++i) {
        std::cin >> s[i];
        numlen[i] = s[i].length();
    }
    std::cin >> K;

    for (p[0] = 1, i = 1; i < 51; ++i) p[i] = p[i - 1] * 10 % K;
    for (i = 0; i < N; ++i) {
        for (int j = 0; j < s[i].length(); ++j) {
            arr[i] = (arr[i] * 10 + (s[i][j] - 48)) % K;
        }
    }
    memset(dp, -1, sizeof dp);

    ll num = dfs(0, 0);
    ll den = gcd(num, f);

    std::cout << num / den << '/' << f / den;
}