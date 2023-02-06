#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int sudoku[9][9];
bool check[3][9][9];
bool flag = false;

void dfs(int x, int y) {
	if (x == 9) {
		flag = true;
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				std::cout << sudoku[i][j];
			}
			std::cout << '\n';
		}
		return;
	}
	int ny = y + 1;
	int nx = x + ny / 9;
	ny %= 9;
	if (!sudoku[x][y]) {
		for (int i = 1; i <= 9; ++i) {
			if (flag) break;
			if (!check[0][x][i - 1] && !check[1][y][i - 1] && !check[2][x / 3 * 3 + y / 3][i - 1]) {
				check[0][x][i - 1] = check[1][y][i - 1] = check[2][x / 3 * 3 + y / 3][i - 1] = 1;
				sudoku[x][y] = i;
				dfs(nx, ny);
				check[0][x][i - 1] = check[1][y][i - 1] = check[2][x / 3 * 3 + y / 3][i - 1] = 0;
				sudoku[x][y] = 0;
			}
		}
	}
	else if (!flag) dfs(nx, ny);
}

int main() {
	freopen("input.txt", "r", stdin);
	char c;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			std::cin >> c;
			sudoku[i][j] = c - '0';
			if (c != '0')
				check[0][i][c - '0' - 1] = check[1][j][c - '0' - 1] = check[2][i / 3 * 3 + j / 3][c - '0' - 1] = 1;
		}
	}
	dfs(0, 0);
}