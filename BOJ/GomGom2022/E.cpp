#include <iostream>

const int LEN = 100'000;
int N, L;
double x[LEN], w[LEN];
double a, b;

int main() {
	std::cin >> N >> L;
	for (int i = 0; i < N; ++i) std::cin >> x[i];
	for (int i = 0; i < N; ++i) std::cin >> w[i];
	for (int i = 0; i < N; ++i) {
		a += w[i] * x[i];
		b += w[i];
	}
	std::cout.precision(10);
	std::cout << a / b;
}