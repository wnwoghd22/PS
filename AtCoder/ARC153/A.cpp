#include <iostream>

int main() {
	int N;
	std::cin >> N;
	--N;
	int a = 1, b = 0, c = 0, d = 0, e = 0, f = 0;
	f += N % 10; N /= 10;
	e += N % 10; N /= 10;
	d += N % 10; N /= 10;
	c += N % 10; N /= 10;
	b += N % 10; N /= 10;
	a += N % 10; N /= 10;
	int result = a * 110000000 + b * 1000000 + c * 100000 + d * 11000 + e * 101 + f * 10;
	std::cout << result;
}