#include <iostream>
#include <cstring>

const int LEN = 51;
int R, C, T;
int map[LEN][LEN];
int temp[LEN][LEN];
int upper, lower;

void diffuse() {
	memset(temp, 0, sizeof temp);
	for (int r = 1; r <= R; ++r) {
		for (int c = 1; c <= C; ++c) {
			if (map[r][c] < 5) continue;

			int amount = map[r][c] / 5;

			if (r > 1 && map[r - 1][c] != -1) temp[r - 1][c] += amount, temp[r][c] -= amount;
			if (r < R && map[r + 1][c] != -1) temp[r + 1][c] += amount, temp[r][c] -= amount;
			if (c > 1 && map[r][c - 1] != -1) temp[r][c - 1] += amount, temp[r][c] -= amount;
			if (c < C && map[r][c + 1] != -1) temp[r][c + 1] += amount, temp[r][c] -= amount;
		}
	}
	for (int r = 1; r <= R; ++r)
		for (int c = 1; c <= C; ++c)
			map[r][c] += temp[r][c];
}
void circulate() {
	for (int i = upper - 1; i > 1; --i) map[i][1] = map[i - 1][1];
	for (int i = 1; i < C; ++i) map[1][i] = map[1][i + 1];
	for (int i = 1; i < upper; ++i) map[i][C] = map[i + 1][C];
	for (int i = C; i > 2; --i) map[upper][i] = map[upper][i - 1];
	map[upper][2] = 0;

	for (int i = lower + 1; i < R; ++i) map[i][1] = map[i + 1][1];
	for (int i = 1; i < C; ++i) map[R][i] = map[R][i + 1];
	for (int i = R; i > lower; --i) map[i][C] = map[i - 1][C];
	for (int i = C; i > 2; --i) map[lower][i] = map[lower][i - 1];
	map[lower][2] = 0;
}
int get_sum() {
	int result = 2;
	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j)
			result += map[i][j];
	}
	return result;
}
void print() {
	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j)
			std::cout << map[i][j] << ' ';
		std::cout << '\n';
	}
	std::cout << get_sum() << '\n';
}

void simulate() {
	diffuse();
	circulate();
	// print();
}

int main() {
	std::cin >> R >> C >> T;
	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			std::cin >> map[i][j];
			if (!~map[i][j]) {
				if (!upper) upper = i, lower = i + 1;
			}
		}
	}
	while (T--) simulate();
	std::cout << get_sum();
}