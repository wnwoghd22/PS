#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int map[50][50];
int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 }, dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int N;

int hunt(int x, int y) {
    int result = 0, d, l, nx, ny;
    for (d = 0; d < 8; ++d) {
        for (l = 1; l < N; ++l) {
            nx = x + dx[d] * l, ny = y + dy[d] * l;
            if (nx < 0 || nx > N || ny < 0 || ny > N) break;
            if (map[nx][ny] == 1 || map[nx][ny] == 3) break;
            if (map[nx][ny] == 2) ++result;
        }
    }
    return result;
}

int solve() {
    int i, j, result = 0;
    scanf("%d", &N);
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            scanf("%d", &map[i][j]);
        }
    }
    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
            if (map[i][j] == 1)
                result += hunt(i, j);

    return result;
}

int main() {
    freopen("input.txt", "r", stdin);
    int t, T;
    scanf("%d", &T);
    for (t = 1; t <= T; ++t)
        printf("#%d %d\n", t, solve());
}