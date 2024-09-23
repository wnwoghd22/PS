#include <iostream>
#include <cmath>

const int MAX = 200'000;

double get_distance(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int posX[MAX];
int posY[MAX];
double toRight[MAX + 2];
double toLeft[MAX + 2];

int main() {
	std::cout << std::fixed;
	std::cout.precision(7);

	int N, Q;
	std::cin >> N >> Q;
	for (int i = 0; i < N; ++i) std::cin >> posX[i];
	for (int i = 0; i < N; ++i) std::cin >> posY[i];

	for (int i = 1; i < N; ++i) {
		double dist = get_distance(posX[i - 1], posY[i - 1], posX[i], posY[i]);
		if (posY[i - 1] > posY[i]) {
			toRight[i] = dist;
			toLeft[i] = dist * 3;
		}
		if (posY[i - 1] == posY[i]) {
			toRight[i] = dist * 2;
			toLeft[i] = dist * 2;
		}
		if (posY[i - 1] < posY[i]) {
			toRight[i] = dist * 3;
			toLeft[i] = dist;
		}
		toRight[i] += toRight[i - 1];
		toLeft[i] += toLeft[i - 1];
	}
	while (Q--) {
		int i, j;
		std::cin >> i >> j;
		if (i < j) std::cout << toRight[j - 1] - toRight[i - 1] << '\n';
		else std::cout << toLeft[i - 1] - toLeft[j - 1] << '\n';
	}
}
