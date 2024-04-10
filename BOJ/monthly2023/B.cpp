#include <iostream>

typedef long double ld;

int N;
int x[5000];
int y[5000];
ld sum;

ld dist(int i, int j) {
	return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> x[i] >> y[i];
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			sum += dist(i, j);
		}
	}
	std::cout << std::fixed;
	std::cout.precision(7);
	std::cout << (ld)2 / N * sum;
}