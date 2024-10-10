#include <iostream>

const int LEN = 1000;
int map[LEN][LEN];
int H, W;
int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, -1, 1 };

int main() {
	std::cin >> H >> W;
	for (int i = 0; i < H; ++i)
		for (int j = 0; j < W; ++j)
			std::cin >> map[i][j];

	int result = 0;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (!~map[i][j]) continue;
			bool hill = true;
			for (int k = 0; k < 4; ++k) {
				int di = i + dx[k], dj = j + dy[k];
				if (di < 0 || di >= H || dj < 0 || dj >= W || !~map[di][dj]) continue;
				int diff = map[i][j] - map[di][dj];
				if (abs(diff) > 1) {
					result = -1;
					break;
				}
				if (diff < 0) hill = false;
			}
			if (!~result) break;
			if (map[i][j] > 0 && hill) ++result;
		}
		if (!~result) break;
	}
	std::cout << result;
}
