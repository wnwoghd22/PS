#include <iostream>

int main() {
	int N, m, M, T, R, X, C = 0;
	std::cin >> N >> m >> M >> T >> R;
	if (m + T > M) {
		std::cout << -1;
		return 0;
	}
	X = m;
	while (N) {
		if (X + T <= M) X += T, N--;
		else X = std::max(m, X - R);
		C++;
	}
	std::cout << C;
}