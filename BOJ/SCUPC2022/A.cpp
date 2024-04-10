#include <iostream>
#include <vector>

std::vector<int> getPi(std::string s) {
    std::vector<int> pi(s.length(), 0);
    int j = 0;

    for (int i = 1; i < s.length(); ++i) {
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) pi[i] = ++j;
    }

    return pi;
}

std::vector<int> kmp(std::string T, std::string P) {
    std::vector<int> result;
    std::vector<int> pi = getPi(P);

    int t = T.length(), p = P.length(), j = 0;

    for (int i = 0; i < t; ++i) {
        while (j > 0 && T[i] != P[j]) j = pi[j - 1];
        if (T[i] == P[j]) {
            if (j == p - 1) {
                result.push_back(i - p + 1);
                j = pi[j];
            }
            else ++j;
        }
    }
    return result;
}

int main() {
    int N;
    std::cin >> N;
    std::string S;
    std::cin >> S;

    std::vector<int> answer = kmp(S, "bigdata");
    int b = answer.size();
    int s = N - b;
    if (b >= s) {
        std::cout << "bigdata? ";
    }
    if (b <= s) {
        std::cout << "security!";
    }

    return 0;
}