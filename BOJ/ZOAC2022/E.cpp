#include <iostream>
#include <queue>

std::string map[1000];
bool visited[1000][1000];
int N, M;

bool bfs(const int r, const int c) {
	int max_r = r, max_c = c;
	std::queue<std::pair<int, int>> q;
	q.push({ r, c });
	visited[r][c] = true;
	while (!q.empty()) {
		auto [x, y] = q.front(); q.pop();
		if (x != r && y > 0 && y == c && map[x][y - 1] == map[x][y]) return 0;
		if (x < N - 1) {
			if (y == c && !visited[x + 1][y] && map[x + 1][y] == map[x][y]) {
				max_r = x + 1;
				visited[x + 1][y] = true;
				q.push({ x + 1, y });
			}
			if (y != c) {
				if (x == max_r) {
					if (map[x + 1][y] == map[x][y]) return 0;
				}
				else {
					if (map[x + 1][y] != map[x][y]) return 0;
					if (!visited[x + 1][y] && map[x + 1][y] == map[x][y]) {
						visited[x + 1][y] = true;
						q.push({ x + 1, y });
					}
				}
			}
		}
		if (y < M - 1) {
			if (x == r && !visited[x][y + 1] && map[x][y + 1] == map[x][y]) {
				max_c = y + 1;
				visited[x][y + 1] = true;
				q.push({ x, y + 1 });
			}
			if (x != r) {
				if (y == max_c) {
					if (map[x][y + 1] == map[x][y]) return 0;
				}
				else {
					if (map[x][y + 1] != map[x][y]) return 0;
					if (!visited[x][y + 1] && map[x][y + 1] == map[x][y]) {
						visited[x][y + 1] = true;
						q.push({ x, y + 1 });
					}
				}
			}
		}
	}
	return 1;
}

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> map[i];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (!visited[i][j] && !bfs(i, j)) {
				std::cout << "BaboBabo";
				return 0;
			}
		}
	}
	std::cout << "dd";
}