#include <iostream>
#include <algorithm>

int main() {
	int count, cost;
	std::cin >> count >> cost;

	int discount5 = count >= 5 ? std::max(cost - 500, 0) : cost;
	int discount10 = count >= 10 ? cost - cost / 10 : cost;
	int discount15 = count >= 15 ? std::max(cost - 2000, 0) : cost;
	int discount20 = count >= 20 ? cost - cost / 4 : cost;

	std::cout << std::min({ discount5, discount10, discount15, discount20 });
}