#include <iostream>
#include <vector>

std::vector<std::string> map;
int R, C;

int dfs(int x, int y, int visited) {
    int result = 0;

    if (x > 0 && !(visited & 1 << map[x - 1][y] - 'A'))
        result = std::max(result, dfs(x - 1, y, visited | 1 << map[x - 1][y] - 'A'));

    if (x < R - 1 && !(visited & 1 << map[x + 1][y] - 'A'))
        result = std::max(result, dfs(x + 1, y, visited | 1 << map[x + 1][y] - 'A'));
    
    if (y > 0 && !(visited & 1 << map[x][y - 1] - 'A'))
        result = std::max(result, dfs(x, y - 1, visited | 1 << map[x][y - 1] - 'A'));

    if (y < C - 1 && !(visited & 1 << map[x][y + 1] - 'A'))
        result = std::max(result, dfs(x, y + 1, visited | 1 << map[x][y + 1] - 'A'));

    return result + 1;
}

int main() {
    std::string s;
    std::cin >> R >> C;
    for (int i = 0; i < R; ++i) {
        std::cin >> s;
        map.push_back(s);
    }
    std::cout << dfs(0, 0, 1 << map[0][0] - 'A');
}