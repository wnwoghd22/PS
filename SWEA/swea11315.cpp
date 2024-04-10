#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ABS(x) ((x) > 0 ? (x) : -(x))
#define NORM(x) ((x) == 0 ? 0 : (x) / ABS(x))

int N;
char A[20][21];

int check(int x, int y) {
	int d, l, dx, dy, nx, ny;
	for (d = 0, dx = 1, dy = 1; d < 4; ++d) {
		l = 1;
		while (l < 5) {
			nx = x + dx * l, ny = y + dy * l;
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) break;
			if (A[nx][ny] == '.') break;
			++l;
		}
		if (l == 5) return 1;

		// linear transformation
		nx = dx - dy, ny = dx + dy;
		dx = NORM(nx), dy = NORM(ny);
	}
	return 0;
}

int solve() {
	int i, j;
	scanf("%d", &N);
	for (i = 0; i < N; ++i) scanf("%s", A[i]);

	for (i = 0; i < N; ++i) printf("%s\n", A[i]);
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			if (A[i][j] == 'o' && check(i, j))
				return 1;
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	int t, T;
	scanf("%d", &T);
	for (t = 1; t <= T; ++t)
		printf("#%d %s\n", t, solve() ? "YES" : "NO");
}