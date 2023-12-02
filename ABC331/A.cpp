#include <iostream>
#include <string>

int M, D;
int y, m, d;

int main() {
	std::cin >> M >> D >> y >> m >> d;
	++d;
	if (d == D + 1) {
		d = 1;
		++m;
	}
	if (m == M + 1) {
		m = 1;
		++y;
	}
	std::cout << y << ' ' << m << ' ' << d;
}