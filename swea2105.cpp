#include <iostream>

bool checked[101];
int map[100][100];
int N;

int check(int x, int y) {
    int result = -1;

    for (int i = 1; i <= y; ++i) {
        for (int j = 1; x + j + i < N && y + j < N; ++j) { // rectangle is inside map (IMPORTANT: y + j < N)
            bool flag = true;
            for (int k = 0; k <= 100; ++k) checked[k] = false;
            checked[map[x][y]] = true;
            for (int i1 = 1; i1 <= i; ++i1) {
                if (checked[map[x + i1][y - i1]]) return result;
                checked[map[x + i1][y - i1]] = true;
            }
            for (int nx = x + i, ny = y - i, i1 = 1; i1 <= j; ++i1) {
                if (checked[map[nx + i1][ny + i1]]) {
                    flag = false;
                    break;
                }
                checked[map[nx + i1][ny + i1]] = true;
            }
            if (!flag) continue;

            for (int nx = x + i + j, ny = y - i + j, i1 = 1; i1 <= i; ++i1) {
                if (checked[map[nx - i1][ny + i1]]) {
                    flag = false;
                    break;
                }
                checked[map[nx - i1][ny + i1]] = true;
            }
            if (!flag) continue;

            for (int nx = x + j, ny = y + j, i1 = 1; i1 < j; ++i1) {
                if (checked[map[nx - i1][ny - i1]]) {
                    flag = false;
                    break;
                }
                checked[map[nx - i1][ny - i1]] = true;
            }
            if (!flag) continue;
            result = std::max(result, (i + j) * 2);
        }
    }

    return result;
}

int solve() {
    std::cin >> N;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            std::cin >> map[i][j];
    int result = -1;
    for (int i = 0; i < N - 2; ++i) {
        for (int j = 1; j < N - 1; ++j) {
            int cur = check(i, j);
            if (cur > result) {
                result = cur;
            }
            // result = std::max(result, check(i, j));    
        }
    }
    return result;
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}