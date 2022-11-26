#include <iostream>
#include <algorithm>

int main() {
	int N;
	char c;
	std::cin >> N;
	int minX = N, maxX = 0, minY = N, maxY = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> c;
			if (c == 'G') {
				minX = std::min(minX, i);
				maxX = std::max(maxX, i);
				minY = std::min(minY, j);
				maxY = std::max(maxY, j);
			}
		}
	}

	int ctrlX = N, ctrlY = N;
	if (minX == maxX) ctrlX = 0;
	if (minY == maxY) ctrlY = 0;
	ctrlX = std::min({ ctrlX, maxX, N - minX - 1 });
	ctrlY = std::min({ ctrlY, maxY, N - minY - 1 });
	std::cout << ctrlX + ctrlY;
}