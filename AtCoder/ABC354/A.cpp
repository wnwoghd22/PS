#include <iostream>

int main() {
	int H;
	std::cin >> H;
	int ret = 1;
	while ((1 << ret) - 1 <= H) ++ret;
	std::cout << ret;
}