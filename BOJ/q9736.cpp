#include <iostream>
#include <algorithm>
#include <cstring>
#include <deque>

const int LEN = 101;
const int INF = 1e7;
const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { 1, 0, -1, 0 };

char map[LEN][LEN];
int T, H, W, p, pos[2], d[3][LEN][LEN];
std::deque<int> dq;

int solve() {
	p = 0;
	memset(d, -1, sizeof d);
	std::cin >> H >> W;
	for (int i = 0; i < H; ++i) {
		std::cin >> map[i];
		for (int j = 0; j < W; ++j) {
			if (map[i][j] == '$')
				pos[p++] = i * W + j;
		}
	}

	for (int k = 0; k <= 1; ++k) {
		d[k][pos[k] / W][pos[k] % W] = 0;
		dq.push_back(pos[k]);
		while (dq.size()) {
			int x = dq.front() / W;
			int y = dq.front() % W;
			dq.pop_front();

			for (int di = 0, nx, ny; di < 4; ++di) {
				nx = x + dx[di]; ny = y + dy[di];
				if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
				if (~d[k][nx][ny]) continue;
				if (map[nx][ny] == '*') continue;
				if (map[nx][ny] == '#') {
					d[k][nx][ny] = d[k][x][y] + 1;
					dq.push_back(nx * W + ny);
				}
				else {
					d[k][nx][ny] = d[k][x][y];
					dq.push_front(nx * W + ny);
				}
			}
		}
	}

	/*for (int k = 0; k <= 1; ++k) {
		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < W; ++j) std::cout << d[k][i][j] << ' ';
			std::cout << '\n';
		}
		std::cout << '\n';
	}*/

	for (int i = 0; i < W; ++i) {
		if (map[0][i] != '*') d[2][0][i] = map[0][i] == '#', dq.push_back(i);
		if (map[H - 1][i] != '*') d[2][H - 1][i] = map[H - 1][i] == '#', dq.push_back(i + W * (H - 1));
	}
	for (int i = 1; i < H - 1; ++i) {
		if (map[i][0] != '*') d[2][i][0] = map[i][0] == '#', dq.push_back(W * i);
		if (map[i][W - 1] != '*') d[2][i][W - 1] = map[i][W - 1] == '#', dq.push_back(W * i + W - 1);
	}
	while (dq.size()) {
		int x = dq.front() / W;
		int y = dq.front() % W;
		dq.pop_front();

		for (int di = 0, nx, ny; di < 4; ++di) {
			nx = x + dx[di]; ny = y + dy[di];
			if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
			if (~d[2][nx][ny]) continue;
			if (map[nx][ny] == '*') continue;
			if (map[nx][ny] == '#') {
				d[2][nx][ny] = d[2][x][y] + 1;
				dq.push_back(nx * W + ny);
			}
			else {
				d[2][nx][ny] = d[2][x][y];
				dq.push_front(nx * W + ny);
			}
		}
	}
	int ret = d[2][pos[0] / W][pos[0] % W] + d[2][pos[1] / W][pos[1] % W];
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (~d[0][i][j] && ~d[1][i][j] && ~d[2][i][j])
				ret = std::min(ret, d[0][i][j] + d[1][i][j] + d[2][i][j] - 2 * (map[i][j] == '#'));
		}
	}

	return ret;
}

int main() {
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';
}