#include <iostream>
#include <queue>

std::priority_queue<int, std::vector<int>, std::greater<int>> A;
std::priority_queue<int, std::vector<int>, std::less<int>> B;

int main() {
    int N, result = 0;
    std::cin >> N;

    for (int a, i = 0; i < N; ++i) std::cin >> a, A.push(a);
    for (int b, i = 0; i < N; ++i) std::cin >> b, B.push(b);
    while (N--) result += A.top() * B.top(), A.pop(), B.pop();

    std::cout << result;
}