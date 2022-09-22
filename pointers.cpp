#include <iostream>

int main()
{
    int a = 2, b = 3, * arr = &a;
    arr[0] = 1;
    std::cin >> b;
    std::cout << &a << '\n' << &b << '\n';
    std::cout << a << '\n' << *(arr + 3) << '\n' << *(arr - 3);

    return 0;
}