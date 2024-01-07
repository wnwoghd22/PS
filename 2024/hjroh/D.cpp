#include <iostream>

const int LEN = 1001;
bool A[LEN][LEN];
int N, M, Q, sum;

int main() {
	std::cin >> N >> M >> Q;
	sum = N * M;
	for (int i = 0, q, x, y, dx, dy; i < Q; ++i) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> dy >> dx >> y >> x;
			while (y > 0 && y <= N && x > 0 && x <= M && !A[y][x]) {
				sum--;
				A[y][x] = 1;
				y += dy;
				x += dx;
			}
		}
		if (q == 2) {
			std::cin >> y >> x;
			std::cout << A[y][x] << '\n';
		}
		if (q == 3) std::cout << sum << '\n';
	}
}
