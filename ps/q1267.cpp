#include <iostream>

int N, y, m;
int main() {
	std::cin >> N;
	for (int i = 0, t; i < N; ++i) {
		std::cin >> t;
		y += (t / 30 + 1) * 10;
		m += (t / 60 + 1) * 15;
	}
	if (y == m) std::cout << "Y M " << y;
	else if (y < m) std::cout << "Y " << y;
	else std::cout << "M " << m;
}