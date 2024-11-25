#include <iostream>

int main() {
	int d, h, w;
	std::cin >> d >> h >> w;
	double k = sqrt(h * h + w * w);
	std::cout << (int)(h * d / k) << ' ' << (int)(w * d / k);
}