#include <iostream>

int temp_size[100][100];
int temp_dir[100][100];
int temp_max[100][100];

int size[100][100];
int dir[100][100];
int N, M, K, x, y, s, d;

void move(int i, int j) {
    int nx, ny;
    switch (dir[i][j]) {
    case 1:
        nx = i - 1, ny = j;
        if (nx == 0) dir[i][j] = 2, size[i][j] /= 2;
        break;
    case 2:
        nx = i + 1, ny = j;
        if (nx == N - 1) dir[i][j] = 1, size[i][j] /= 2;
        break;
    case 3:
        nx = i, ny = j - 1;
        if (ny == 0) dir[i][j] = 4, size[i][j] /= 2;
        break;
    case 4:
        nx = i, ny = j + 1;
        if (ny == N - 1) dir[i][j] = 3, size[i][j] /= 2;
        break;
    }
    if (size[i][j]) {
        if (size[i][j] > temp_max[nx][ny]) {
            temp_max[nx][ny] = size[i][j];
            temp_dir[nx][ny] = dir[i][j];
        }
        temp_size[nx][ny] += size[i][j];
    }
}

int simulate() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            temp_size[i][j] = 0;
            temp_dir[i][j] = 0;
            temp_max[i][j] = 0;
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (size[i][j]) move(i, j);
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            dir[i][j] = temp_dir[i][j];
            size[i][j] = temp_size[i][j];
        }
    }
}

int solve() {
    std::cin >> N >> M >> K;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            size[i][j] = 0, dir[i][j] = 0;
        }
    }
    while (K--) {
        std::cin >> x >> y >> s >> d;
        size[x][y] = s; dir[x][y] = d;
    }
    while (M--) simulate();
    int result = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            result += size[i][j];
    return result;
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}