#include <iostream>

int map[100][100];
int col_sum[100];
int row_sum[100];

int main() {
	int N, M, weight = -1e9;
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			std::cin >> map[i][j];
			col_sum[j] += map[i][j];
			row_sum[i] += map[i][j];
		}
	}

	for (int i1 = 0; i1 < N - 1; ++i1) {
		for (int i2 = i1 + 1; i2 < N; ++i2) {
			int height = i2 - i1 - 1;
			
			for (int j1 = 0; j1 < M - 1; ++j1) {
				for (int j2 = j1 + 1; j2 < M; ++j2) {
					int width = j2 - j1 - 1;

					int current_weight =
						row_sum[i1] + row_sum[i2] + col_sum[j1] + col_sum[j2]
						- map[i1][j1] - map[i1][j2] - map[i2][j1] - map[i2][j2]
						+ height * width;

					weight = std::max(weight, current_weight);
				}
			}
		}
	}
	std::cout << weight;
}