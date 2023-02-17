#include <iostream>
#include <cstring>

const int LEN = 100;
int N, map[LEN][LEN];
int wormholes[5];
int wormhole_pos[10][2];

// dir: 0: up, 1: down, 2: left, 3: right, 5: invalid
int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, -1, 1 };
int mat[4][5] = { // IMPORTANT: be careful when make adj condition matrix
  5, 3, 2, 5, 5,
  3, 5, 5, 2, 5,
  0, 1, 5, 5, 5,
  5, 5, 1, 0, 5
};

void get_map() {
    std::cin >> N;
    for (int i = 0; i < 5; ++i) wormholes[i] = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> map[i][j];
            if (map[i][j] >= 6 && map[i][j] <= 10) {
                int w = map[i][j] - 6;
                map[i][j] += 5 * wormholes[w];
                int other = w + 5 * (wormholes[w] ^ 1);
                wormhole_pos[other][0] = i;
                wormhole_pos[other][1] = j;
                // std::cout << map[i][j] << ' ' << w << ' ' << other << ' ' << wormhole_pos[other][0] << ' ' << wormhole_pos[other][1] << '\n';
                ++wormholes[w];
            }
        }
    }
}

int get_score(int x, int y) {
    // std::cout << x << ' ' << y << '\n';
    int result = 0;
    for (int d = 0; d < 4; ++d) {
        // for (int d = 3; d == 3; ++d) { 
        int cur = 0;
        int dir = d;
        int nx = x, ny = y;
        while (true) {

            // std::cout << nx << ' ' << ny << '\n';
            nx += dx[dir];
            ny += dy[dir];
            // std::cout << nx << ' ' << ny << '\n';
            if (nx == x && ny == y) break;
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
                cur = cur * 2 + 1;
                break;
            }
            if (!~map[nx][ny]) break; // black hole
            if (!map[nx][ny]) continue;
            if (map[nx][ny] < 6) { // wall
                // std::cout << map[nx][ny] << '\n';
                // std::cout << dir << '\n';
                dir = mat[dir][map[nx][ny] - 1];
                // std::cout << dir << '\n';
                if (dir == 5) {
                    cur = cur * 2 + 1;
                    break;
                }
                else {
                    ++cur;
                    continue;
                }
            }
            // std::cout << map[nx][ny] << ' ' << nx << ' ' << ny << '\n';
            int w = map[nx][ny] - 6; // get wormhole index
            nx = wormhole_pos[w][0];
            ny = wormhole_pos[w][1];
            // std::cout << "other: " << nx << ' ' << ny << '\n';
        }
        // std::cout << d << ' ' << cur << ' ';
        if (cur > result) result = cur;
    }
    // std::cout << '\n';
    return result;
}

int solve() {
    get_map();
    int result = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!map[i][j]) {
                int cur = get_score(i, j);
                if (cur > result) result = cur;
            }
        }
    }
    // get_score(2,3);
    return result;
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}