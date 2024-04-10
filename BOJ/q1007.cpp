#include <iostream>
#include <cmath>

const double MAX = 1e9;
double result = MAX;
double pos[20][2];
int N;

double magnitude(double x, double y) { return sqrt(x * x + y * y); }

void dfs(int idx, int bit, int depth) {
	if (depth == N / 2) {
		double x = 0, y = 0;
		for (int i = 0; i < N; ++i) {
			if (bit & 1 << i) x += pos[i][0], y += pos[i][1];
			else x -= pos[i][0], y -= pos[i][1];
		}
		result = std::min(result, magnitude(x, y));
		return;
	}
	for (int i = idx; i < N; ++i) dfs(i + 1, bit | 1 << i, depth + 1);
}

int main() {
	int T;
	std::cout << std::fixed;
	std::cout.precision(7);

	std::cin >> T;
	while (T--) {
		result = MAX;
		std::cin >> N;
		for (int i = 0; i < N; ++i) {
			std::cin >> pos[i][0] >> pos[i][1];
		}
		dfs(0, 0, 0);

		std::cout << result << '\n';
	}
}