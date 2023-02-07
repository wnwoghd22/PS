#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

const int INF = 1e9;
int phase[6][15][12];
int temp[15][12];
int after[15][12];
int fallen[15][12];
int explosion[15][12];
int N, W, H;
int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };

void explode(int x, int y) {
    if (explosion[x][y]) return;
    explosion[x][y] = true;
    for (int d = 0; d < 4; ++d) {
        for (int l = 2; l <= temp[x][y]; ++l) {
            int nx = x + dx[d] * (l - 1), ny = y + dy[d] * (l - 1);
            if (0 <= nx && nx < H && 0 <= ny && ny < W) {
                if (temp[nx][ny]) explode(nx, ny);
            }
        }
    }
}

void eliminate() {
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            after[i][j] = temp[i][j];

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (!explosion[i][j]) continue;
            after[i][j] = 0;
            for (int d = 0; d < 4; ++d) {
                for (int l = 2; l <= temp[i][j]; ++l) {
                    int nx = i + dx[d] * (l - 1), ny = j + dy[d] * (l - 1);
                    if (0 <= nx && nx < H && 0 <= ny && ny < W) after[nx][ny] = 0;
                }
            }
        }
    }
}

void fall() {
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            fallen[i][j] = 0;

    for (int w = 0; w < W; ++w) {
        int u = H, d = H - 1;
        while (--u >= 0) {
            if (after[u][w]) {
                fallen[d--][w] = after[u][w];
            }
        }
    }
}

void simulate(int p, int w) {
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            temp[i][j] = phase[p][i][j], explosion[i][j] = false;
    int h = 0;
    while (h < H && !temp[h][w]) ++h;
    if (h >= H) {
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                phase[p + 1][i][j] = phase[p][i][j];
        return;
    }
    explode(h, w);
    eliminate();
    fall();
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            phase[p + 1][i][j] = fallen[i][j];
}

int dfs(int p) {
    if (p == N) {
        int cnt = 0;
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                if (phase[N][i][j]) cnt++;
        return cnt;
    }
    int result = INF;
    for (int w = 0; w < W; ++w) {
        simulate(p, w);
        result = std::min(result, dfs(p + 1));
    }
    return result;
}

int solve() {
    memset(phase, 0, sizeof phase);
    std::cin >> N >> W >> H;
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            std::cin >> phase[0][i][j];
    /*simulate(0, 2);
    std::cout << '\n';
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j)
            std::cout << phase[1][i][j] << ' ';
        std::cout << '\n';
    }
    simulate(1, 2);
    std::cout << '\n';
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j)
            std::cout << phase[2][i][j] << ' ';
        std::cout << '\n';
    }*/

    return dfs(0);
}

int main() {
    freopen("input.txt", "r", stdin);
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) {
        std::cout << '#' << t << ' ' << solve() << '\n';
    }
}