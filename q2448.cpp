#include <iostream>
#include <cmath>

std::string print(int,int);

int main() {
    int n, i, j;
    std::cin >> n;

    for (i = 1; i <= n; ++i) {
        int depth = (i + 2) / 3, mod = i % 3;
        for (j = 0; j < (n / 3) - depth; ++j)
            std::cout << "   ";
        std::cout << print(depth, mod);
        for (j = 0; j < (n / 3) - depth; ++j)
            std::cout << "   ";
        std::cout << '\n';
    }
    return 0;
}

std::string print(int depth, int mod) {
    std::string answer = "";

    if (depth == 1) {
        if (mod == 1) answer = "  *   ";
        if (mod == 2) answer = " * *  ";
        if (mod == 0) answer = "***** ";
    }
    else {
        int offset = pow(2, ceil(log2(depth))) - depth;
        answer += print((depth - offset) / 2, mod);
        for (int i = 0; i < offset; ++i)
            answer += "      ";
        answer += print((depth - offset) / 2, mod);
    }
    return answer;
}