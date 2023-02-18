#include <stdio.h>

int N, M, A[15][15];

int get_max(int x, int y) {
	int c1, c2, d, l, dx, dy, nx, ny;
	c1 = A[x][y];
	for (d = 0, dx = 0, dy = 1; d < 4; ++d) {
		for (l = 1; l < M; ++l) {
			nx = x + dx * l, ny = y + dy * l;
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) break;
			c1 += A[nx][ny];
		}
		l = dx, dx = -dy, dy = l; // linear transformation
	}
	c2 = A[x][y];
	for (d = 0, dx = 1, dy = 1; d < 4; ++d) {
		for (l = 1; l < M; ++l) {
			nx = x + dx * l, ny = y + dy * l;
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) break;
			c2 += A[nx][ny];
		}
		l = dx, dx = -dy, dy = l; // linear transformation
	}
	return c1 > c2 ? c1 : c2;
}

int solve() {
	int i, j, r = 0, c;
	scanf("%d %d", &N, &M);
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			scanf("%d", A[i] + j);
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			c = get_max(i, j);
			if (c > r) r = c;
		}
	}
	return r;
}

int main() {
	int t, T;
	scanf("%d", &T);
	for (t = 1; t <= T; ++t)
		printf("#%d %d\n", t, solve());
}