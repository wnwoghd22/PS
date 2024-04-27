#include <iostream>
#include <algorithm>
#include <queue>

const int LEN = 1001;
const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

int H, W;
char map[LEN][LEN];
bool rooted[LEN][LEN];
bool checked[LEN][LEN];
int visited[LEN][LEN];

int bfs(int r, int c) {
	int mask = r * W + c + 1;
	std::queue<int> q;
	int ret = 1;
	if (!rooted[r][c])
		q.push(r * W + c);
	visited[r][c] = mask;
	checked[r][c] = 1;
	while (q.size()) {
		int x = q.front() / W;
		int y = q.front() % W;
		q.pop();
		for (int d = 0, nx, ny; d < 4; ++d) {
			nx = x + dx[d];
			ny = y + dy[d];
			if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
			if (visited[nx][ny] == mask) continue;
			if (map[nx][ny] == '#') continue;
			ret++;
			checked[nx][ny] = 1;
			visited[nx][ny] = mask;
			if (!rooted[nx][ny]) q.push(nx * W + ny);
		}
	}
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> H >> W;
	for (int i = 0; i < H; ++i) {
		std::cin >> map[i];
		for (int j = 0; j < W; ++j) {
			if (map[i][j] == '#') {
				for (int d = 0, nx, ny; d < 4; ++d) {
					nx = i + dx[d];
					ny = j + dy[d];
					if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
					rooted[nx][ny] = 1;
				}
			}
		}
	}
	int ret = 1;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (map[i][j] != '#' && !checked[i][j]) {
				ret = std::max(ret, bfs(i, j));
			}
		}
	}
	std::cout << ret;
}