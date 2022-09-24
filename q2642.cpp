#include <iostream>

enum face { F, R, B, L, U, D };
int cube[6];
int map[6][6];

void rotate(int dir) {
	int temp = cube[F];
	switch (dir) {
	case U:
		cube[F] = cube[U]; cube[U] = cube[B];
		cube[B] = cube[D]; cube[D] = temp;
		break;
	case D:
		cube[F] = cube[D]; cube[D] = cube[B];
		cube[B] = cube[U]; cube[U] = temp;
		break;
	case R:
		cube[F] = cube[R]; cube[R] = cube[B];
		cube[B] = cube[L]; cube[L] = temp;
		break;
	case L:
		cube[F] = cube[L]; cube[L] = cube[B];
		cube[B] = cube[R]; cube[R] = temp;
		break;
	}
}

void dfs(int x, int y) {
	cube[F] = map[x][y];
	if (x > 0 && map[x - 1][y] && !cube[U])
		rotate(U), dfs(x - 1, y), rotate(D);

	if (x < 5 && map[x + 1][y] && !cube[D])
		rotate(D), dfs(x + 1, y), rotate(U);

	if (y > 0 && map[x][y - 1] && !cube[L])
		rotate(L), dfs(x, y - 1), rotate(R);

	if (y < 5 && map[x][y + 1] && !cube[R])
		rotate(R), dfs(x, y + 1), rotate(L);
}

int main() {
	int x, y;

	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 6; ++j) {
			std::cin >> map[i][j];
			if (map[i][j] == 1) x = i, y = j;
		}

	dfs(x, y);

	if (cube[F] && cube[R] && cube[B] && cube[L] && cube[U] && cube[D])
		std::cout << cube[B];
	else
		std::cout << 0;
}