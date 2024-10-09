#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

const int LEN = 200'001;
char S[LEN], Q[LEN], P[LEN];
int len;

int check(std::string s, std::string key) {
    int result = 0;
    for (int j, i = 0; i < s.length(); i += key.length()) {
        for (j = 0; j < key.length(); ++j) {
            if (s[i + j] != key[j]) break;
        }
        if (j == key.length())
            result++;
    }
    return result;
}

int main() {
    std::cin >> S >> Q;
    len = strlen(S);
    for (int i = 0; i < len; ++i) {
        int c = Q[i] - S[i];
        if (c == 0) {
            P[i] = 'Z';
            continue;
        }
        if (c < 0) c += 26;
        P[i] = c + 'A' - 1;
    }

    std::string target(P);
    std::string key;
    std::string result(P);
    int keylen = len;

    for (int i = 1; i <= sqrt(len); ++i) {
        if (len % i) continue;
        key = target.substr(0, i);
        if (check(target, key) == len / i) {
            if (i < keylen) {
                keylen = i;
                result = key;
            }
        }
        key = target.substr(0, len / i);
        if (check(target, key) == i) {
            if (len / i < keylen) {
                keylen = len / i;
                result = key;
            }
        }

    }
    std::cout << result;
}