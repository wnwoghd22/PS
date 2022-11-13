#include <iostream>
#include <vector>

int B, N;
std::string s[1000];
std::vector<int> Pi[1000];

void getPi(int idx) {
    Pi[idx] = std::vector<int>(s[idx].length(), 0);
    int j = 0;

    for (int i = 1; i < s[idx].length(); ++i) {
        while (j > 0 && s[idx][i] != s[idx][j]) j = Pi[idx][j - 1];
        if (s[idx][i] == s[idx][j]) Pi[idx][i] = ++j;
    }
}

int kmp(std::string T, int idx) {
    int result = 0;
    std::string P = s[idx];
    std::vector<int>& pi = Pi[idx];

    int t = T.length(), p = P.length(), j = 0;

    for (int i = 0; i < t; ++i) {
        while (j > 0 && T[i] != P[j]) j = pi[j - 1];
        if (T[i] == P[j]) {
            if (j == p - 1) {
                ++result;
                j = pi[j];
            }
            else ++j;
        }
    }
    return result;
}

int main() {
    std::cin >> B;
    for (int i = 0; i < B; ++i) {
        std::cin >> s[i];
        getPi(i);
    }
    for (int i = 500; i < 500 + B; ++i) {
        std::cin >> s[i];
        getPi(i);
    }
    std::cin >> N;
    while (N--) {
        int result = 0;
        std::string T;
        std::cin >> T;

        for (int i = 0; i < B; ++i) result -= kmp(T, i);
        for (int i = 500; i < 500 + B; ++i) result += kmp(T, i);
        
        if (result > 0) std::cout << "LOW " << result << '\n';
        if (result < 0) std::cout << "HIGH " << -result << '\n';
        if (!result) std::cout << "GOOD\n";
    }
}