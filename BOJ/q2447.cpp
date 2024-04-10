#include <iostream>

std::string print(int, int);

int main() {
    int n, i, depth = 0;
    std::cin >> n; i = n;

    while ((i /= 3) > 0) ++depth;

    for (i = 0; i < n; ++i) std::cout << print(depth, i) << std::endl;
    return 0;
}

std::string print(int depth, int n) {
    std::string answer;

    if (depth == 0) answer = "*";
    else {
        int m = 1, i, k;
        for (i = 0; i < depth - 1; ++i) m *= 3;
        k = (n / m) % 3;
        if (k == 0)
            answer = print(depth - 1, n) + print(depth - 1, n) + print(depth - 1, n);
        else if (k == 1)
            answer = print(depth - 1, n) + std::string(m, ' ') + print(depth - 1, n);
        else
            answer = print(depth - 1, n) + print(depth - 1, n) + print(depth - 1, n);
    }
    return answer;
}