#include <iostream>

char map[100][101];
int H, W;

int main() {
	std::cin >> H >> W;
	for (int i = 0; i < H; ++i) std::cin >> map[i];
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W - 1; ++j) {
			if (map[i][j] == 'T' && map[i][j + 1] == 'T') {
				map[i][j] = 'P';
				map[i][j + 1] = 'C';
				++j;
			}
		}
	}
	for (int i = 0; i < H; ++i) std::cout << map[i] << '\n';

}