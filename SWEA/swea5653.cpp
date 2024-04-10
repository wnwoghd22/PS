#include <iostream>
#include <queue>
#include <cstring>

struct Info {
    int x, y, s;
};
std::queue<Info> q;
std::queue<Info> activated;
std::queue<int> remains;

int N, M, K;
int map[351][351];
int state[351][351];
int _time[351][351];
int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, -1, 1 };

void print(int x, int y, int w) {
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < w; ++j) {
            std::cout << map[x + i][y + j] << ' ';
        }
        std::cout << '\n';
    }
}

void simulate(int t) {
    std::queue<Info> temp;
    std::queue<Info> tempAct;
    std::queue<int> tempR;

    while (remains.size()) {
        int i = remains.front(); remains.pop();
        if (--i) tempR.push(i);
    }
    while (tempR.size()) {
        remains.push(tempR.front()); tempR.pop();
    }

    while (activated.size()) {
        Info i = activated.front(); activated.pop();
        --state[i.x][i.y];
        for (int d = 0; d < 4; ++d) {
            int nx = i.x + dx[d], ny = i.y + dy[d];
            // std::cout << t << ' ' << nx << ' ' << ny << '\n';
            if (!map[nx][ny]) {
                state[nx][ny] = map[nx][ny] = map[i.x][i.y];
                _time[nx][ny] = t;
                temp.push({ nx, ny, map[i.x][i.y] });
            }
            else if (_time[nx][ny] == t && map[i.x][i.y] > map[nx][ny]) {
                state[nx][ny] = map[nx][ny] = map[i.x][i.y];
                _time[nx][ny] = t;
                temp.push({ nx, ny, map[i.x][i.y] });
            }
        }
        int _s = map[i.x][i.y] - 1;
        if (_s) remains.push(_s);
    }

    while (q.size()) {
        Info i = q.front(); q.pop();
        --state[i.x][i.y];
        if (state[i.x][i.y]) temp.push({ i.x, i.y, map[i.x][i.y] });
        else if (state[i.x][i.y] == 0) {
            activated.push({ i.x, i.y, map[i.x][i.y] });
        }
    }
    while (temp.size()) {
        Info i = temp.front(); temp.pop();
        if (i.s == map[i.x][i.y]) q.push(i);
    }
    // print(145, 145, 10);
}

int solve() {
    q = std::queue<Info>();
    activated = std::queue<Info>();
    remains = std::queue<int>();
    memset(map, 0, sizeof map);
    memset(state, -1, sizeof state);
    memset(_time, -1, sizeof _time);
    std::cin >> N >> M >> K;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cin >> map[150 + i][150 + j];
            // std::cout << map[150 + i][150 + j] << ' ';
            if (map[150 + i][150 + j]) {
                q.push({ 150 + i, 150 + j, map[150 + i][150 + j] });
                _time[150 + i][150 + j] = 0;
                state[150 + i][150 + j] = map[150 + i][150 + j];
            }
        }
    }
    // print(150,150,2);
    for (int t = 1; t <= K; ++t) simulate(t);
    // print(140,140,20);
    // std::cout << q.size() << ' ' << activated.size() << ' ' << remains.size() << '\n';
    return q.size() + activated.size() + remains.size();
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}