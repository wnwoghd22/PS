#include <iostream>
#include <cstring>

bool map[10][10];
bool temp[10][10];
int dx[] = { -1, 0, 1, 0 }, dy[] = { 0, -1, 0, 1 };

void flip(int x, int y) {
	temp[x][y] = !temp[x][y];
	for (int i = 0; i < 4; ++i) {
		int _x = x + dx[i], _y = y + dy[i];
		if (_x < 0 || _x > 9 || _y < 0 || _y > 9) continue;
		temp[_x][_y] = !temp[_x][_y];
	}
}

int main() {
	char c;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			std::cin >> c;
			if (c == 'O') map[i][j] = 1;
		}
	}
	int min = 1e9;
	for (int bit = 0; bit < 1024; ++bit) {
		memcpy(temp, map, sizeof temp);
		int count = 0, flag = 1;
		for (int i = 0; i < 10; ++i) {
			if (bit & (1 << i)) flip(0, i), ++count;
		}
		for (int i = 1; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				if (temp[i - 1][j]) flip(i, j), ++count;
			}
		}
		for (int i = 0; i < 10; ++i) if (temp[9][i]) flag = 0;
		if (flag) min = std::min(min, count);
	}
	std::cout << (min > 100 ? -1 : min);
}