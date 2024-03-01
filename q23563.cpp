#include <iostream>
#include <cstring>
#include <deque>

const int LEN = 501;
const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

int visited[LEN][LEN];
char map[LEN][LEN];

int H, W;
int S, E;

int main() {
	std::cin >> H >> W;
	for (int i = 0; i < H; ++i) std::cin >> map[i];
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (map[i][j] == '#') continue;
			if (map[i][j] == 'S') S = i * W + j;
			if (map[i][j] == 'E') E = i * W + j;
			for (int d = 0; d < 4; ++d) {
				if (map[i + dx[d]][j + dy[d]] == '#')
					map[i][j] = '*';
			}
		}
	}
	std::deque<int> dq;
	dq.push_back(S);
	memset(visited, -1, sizeof visited);
	visited[S / W][S % W] = 0;
	while (dq.size()) {
		int cur = dq.front(); dq.pop_front();
		int x = cur / W, y = cur % W;
		for (int d = 0, nx, ny; d < 4; ++d) {
			nx = x + dx[d];
			ny = y + dy[d];
			if (map[nx][ny] == '#') continue;
			if (~visited[nx][ny]) continue;
			if (map[x][y] == '*' && map[nx][ny] == '*') {
				visited[nx][ny] = visited[x][y];
				dq.push_front(nx * W + ny);
			}
			else {
				visited[nx][ny] = visited[x][y] + 1;
				dq.push_back(nx * W + ny);
			}
		}
	}
	std::cout << visited[E / W][E % W];
}