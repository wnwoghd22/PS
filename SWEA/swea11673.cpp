#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int adj[4][3] = {
	0, 3, 2,
	1, 2, 3,
	2, 1, 0,
	3, 0, 1
};

int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, -1, 1 };
int N, A[100][100];

int solve() {
	int i, j, d = 3, c = 0;
	scanf("%d", &N);
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			scanf("%d", &A[i][j]);

	i = 0, j = 0;
	while (0 <= i && i < N && 0 <= j && j < N) {
		if (A[i][j]) ++c;
		d = adj[d][A[i][j]];
		i += dx[d], j += dy[d];
	}
	return c;
}

int main() {
	freopen("input.txt", "r", stdin);
	int t, T;
	scanf("%d", &T);
	for (t = 1; t <= T; ++t) printf("#%d %d\n", t, solve());
}