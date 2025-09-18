#include <iostream>

int main() {
	int N;
	std::cin >> N;
	int l = 1, r = N;
	while (l <= r) {
		int m = l + r >> 1;
		std::cout << "? " << m << std::endl;
		std::cin >> N;
		if (N < 0) l = m + 1;
		if (N > 0) r = m - 1;
		if (N == 0) {
			l = r = m;
			break;
		}
	}
	std::cout << "= " << r << std::endl;
}