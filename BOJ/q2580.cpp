#include <iostream>

bool c[10][10];
bool r[10][10];
bool s[10][10];
int board[10][10];

int square(int x, int y) {
    return (x / 3) * 3 + (y / 3);
}
bool dfs(int depth) {
    if (depth == 81) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) std::cout << board[i][j]; // << ' ';
            std::cout << '\n';
        }
        return true;
    }
    int x = depth / 9;
    int y = depth % 9;
    if (board[x][y]) {
        return dfs(depth + 1);
    }
    else {
        for (int i = 1; i <= 9; ++i) {
            if (!r[x][i] && !c[y][i] && !s[square(x, y)][i]) {
                r[x][i] = c[y][i] = s[square(x, y)][i] = true;
                board[x][y] = i;

                if (dfs(depth + 1)) return true;

                board[x][y] = 0;
                r[x][i] = c[y][i] = s[square(x, y)][i] = false;
            }
        }
    }
    return false;
}

// 2580, 2239
int main() {
    int i, j;

    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j) {
            //std::cin >> board[i][j];
            scanf("%1d", &board[i][j]);
            if (board[i][j]) {
                r[i][board[i][j]] = true;
                c[j][board[i][j]] = true;
                s[square(i, j)][board[i][j]] = true;
            }
        }
    }
    dfs(0);

    return 0;
}