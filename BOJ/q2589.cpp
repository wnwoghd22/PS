#include <iostream>
#include <cstring>
#include <queue>

const int LEN = 51;
const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

char map[LEN][LEN];
int N, M, visited[LEN][LEN];

int bfs(int x, int y) {
	memset(visited, -1, sizeof visited);
	std::queue<int> q;
	q.push(x * M + y);
	visited[x][y] = 0;
	int ret = 0;
	while (q.size()) {
		x = q.front() / M;
		y = q.front() % M;
		q.pop();
		for (int d = 0, nx, ny; d < 4; ++d) {
			nx = x + dx[d];
			ny = y + dy[d];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			if (!~visited[nx][ny] && map[nx][ny] == 'L') {
				visited[nx][ny] = visited[x][y] + 1;
				ret = std::max(ret, visited[nx][ny]);
				q.push(nx * M + ny);
			}
		}
	}
	return ret;
}

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> map[i];
	
	int ret = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (map[i][j] == 'L') 
				ret = std::max(ret, bfs(i, j));
		}
	}
	std::cout << ret;
}