#include <iostream>

int main() {
    int n;
    std::string s;
    std::cin >> n;
    n++;
    std::cout << "? 1000000000" << std::endl;
    std::cin >> s;
    int i = s.length() - 1;
    std::cout << "!";
    while (n--) {
        int a = 0;
        for (int e = 1, k = 0; i >= 0 && k < 9; --i, ++k, e *= 10) {
            a += (s[i] - '0') * e;
        }
        std::cout << ' ' << a;
    }
    std::cout << std::endl;
}