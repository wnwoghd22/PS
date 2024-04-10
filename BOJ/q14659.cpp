#include <iostream>

int main() {
	int N, h, current = 0, combo = 0, max = 0;
	std::cin >> N;
	while (N--) {
		std::cin >> h;
		if (h < current) combo++, max = std::max(max, combo);
		else current = h, combo = 0;
	}
	std::cout << max;
}