#include <iostream>
#include <cstring>

int R, C, M, r, c, s, d, z, idx;
class Shark {
private:
	int s, d, z;
public:
	Shark(int s, int d, int z) : s(s), d(d), z(z) {}
	int get_z() { return z; }
	std::pair<int, int> swim(int i, int j) {
		std::pair<int, int> result = { 0, 0 };
		int _s = s;
		switch (d) {
		case 1:
			if (i + _s < R - 1) result = { i + _s, j };
			else {
				_s -= R - i - 1;
				if (R - _s - 1 > 0) {
					result = { R - _s - 1, j };
					d = 2;
				}
				else result = { _s - (R - 1), j };
			}
			break;
		case 2:
			if (i - _s > 0) result = { i - _s, j };
			else {
				_s -= i;
				if (_s < R - 1) {
					result = { _s, j };
					d = 1;
				}
				else result = { 2 * (R - 1) - _s, j };
			}
			break;
		case 3:
			if (j + _s < C - 1) result = { i, j + _s };
			else {
				_s -= C - j - 1;
				if (C - _s - 1 > 0) {
					result = { i, C - _s - 1 };
					d = 4;
				}
				else result = { i, _s - (C - 1) };
			}
			break;
		case 4:
			if (j - _s > 0) result = { i, j - _s };
			else {
				_s -= j;
				if (_s < C - 1) {
					result = { i, _s };
					d = 3;
				}
				else result = { i, 2 * (C - 1) - _s };
			}
			break;
		}
		return result;
	}
} *map[100][100], *temp[100][100], *heap[10000];

int fish(int i) {
	for (int j = 0; j < R; ++j) {
		if (map[j][i]) {
			int z = map[j][i]->get_z();
			map[j][i] = 0;
			return z;
		}
	}
	return 0;
}

void swim() {
	memset(temp, 0, sizeof temp);
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (!map[i][j]) continue;
			Shark* sh = map[i][j];
			auto [ni, nj] = sh->swim(i, j);

			if (temp[ni][nj]) {
				if (temp[ni][nj]->get_z() < sh->get_z())
					temp[ni][nj] = sh;
			}
			else temp[ni][nj] = sh;
		}
	}
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (temp[i][j]) map[i][j] = temp[i][j];
			else map[i][j] = 0;
		}
	}
}

int main() {
	std::cin >> R >> C >> M;
	while (M--) {
		std::cin >> r >> c >> s >> d >> z;
		switch (d) {
		case 1: case 2:
			s %= 2 * (R - 1);
			break;
		case 3: case 4:
			s %= 2 * (C - 1);
			break;
		}
		map[r - 1][c - 1] = new Shark(s, d, z);
		heap[idx++] = map[r - 1][c - 1];
	}
	int result = 0;
	for (int i = 0; i < C; ++i) {
		result += fish(i);
		swim();
	}
	for (int i = 0; i < idx; ++i) delete heap[i];
	std::cout << result;
}