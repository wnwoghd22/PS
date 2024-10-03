#include <iostream>

int R, C;

int main() {
	std::cin >> R >> C;
	int ret = 0;
	while (1) {
		if (R > C) std::swap(R, C);
		ret += C / R;
		C %= R;
		if (!C) break;
	}
	std::cout << ret;
}