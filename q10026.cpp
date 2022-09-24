#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

char map[100][101];
bool visited[100][100];
int N;

int bfs(int x, int y) {
    int result = 0;
    std::queue<std::pair<int, int>> q;

    q.push({ x, y });
    visited[x][y] = true;
    ++result;

    while (!q.empty()) {
        x = q.front().first, y = q.front().second; q.pop();

        if (x > 0 && !visited[x - 1][y] && map[x - 1][y] == map[x][y])
            ++result, visited[x - 1][y] = true, q.push({ x - 1, y });
        if (x < N - 1 && !visited[x + 1][y] && map[x + 1][y] == map[x][y])
            ++result, visited[x + 1][y] = true, q.push({ x + 1, y });
        if (y > 0 && !visited[x][y - 1] && map[x][y - 1] == map[x][y])
            ++result, visited[x][y - 1] = true, q.push({ x, y - 1 });
        if (y < N - 1 && !visited[x][y + 1] && map[x][y + 1] == map[x][y])
            ++result, visited[x][y + 1] = true, q.push({ x, y + 1 });
    }
    return result;
}
int bfs_color_blind(int x, int y) {
    int result = 0;
    std::queue<std::pair<int, int>> q;

    q.push({ x, y });
    visited[x][y] = true;
    ++result;

    while (!q.empty()) {
        x = q.front().first, y = q.front().second; q.pop();

        if (x > 0 && !visited[x - 1][y] && (map[x - 1][y] == 'R' || map[x - 1][y] == 'G'))
            ++result, visited[x - 1][y] = true, q.push({ x - 1, y });
        if (x < N - 1 && !visited[x + 1][y] && (map[x + 1][y] == 'R' || map[x + 1][y] == 'G'))
            ++result, visited[x + 1][y] = true, q.push({ x + 1, y });
        if (y > 0 && !visited[x][y - 1] && (map[x][y - 1] == 'R' || map[x][y - 1] == 'G'))
            ++result, visited[x][y - 1] = true, q.push({ x, y - 1 });
        if (y < N - 1 && !visited[x][y + 1] && (map[x][y + 1] == 'R' || map[x][y + 1] == 'G'))
            ++result, visited[x][y + 1] = true, q.push({ x, y + 1 });
    }
    return result;
}


int main() {
    int i, j, areas = 0, areas_blind = 0;
    std::vector<std::pair<int, int>> virus;

    std::cin >> N;
    for (i = 0; i < N; ++i) std::cin >> map[i];

    memset(visited, 0, sizeof visited);
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            if (!visited[i][j])
                bfs(i, j), areas++;
        }
    }

    memset(visited, 0, sizeof visited); 
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            if (!visited[i][j]) {
                if (map[i][j] == 'R' || map[i][j] == 'G') bfs_color_blind(i, j), areas_blind++;
                else bfs(i, j), areas_blind++;
            }
        }
    }

    std::cout << areas << ' ' << areas_blind;
}