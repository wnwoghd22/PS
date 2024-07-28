#include <iostream>

int f(int a, int b, int c) {
    int ret;
    if (a == b && b == c) {
        ret = 10'000 + a * 1000;
    } 
    else if (a == b) {
        ret = 1000 + a * 100;
    }
    else if (b == c) {
        ret = 1000 + b * 100;
    }
    else if (c == a) {
        ret = 1000 + c * 100;
    }
    else {
        int m = a;
        if (b > m) m = b;
        if (c > m) m = c;
        ret = m * 100;
    }
    return ret;
}

int main() {
    int N, ret = 0;
    std::cin >> N;
    for (int i = 0, a, b, c; i < N; ++i) {
        std::cin >> a >> b >> c;
        int cur = f(a, b, c);
        if (cur > ret) ret = cur;
    }
    std::cout << ret;
}