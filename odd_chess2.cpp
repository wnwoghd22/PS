#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int board[18][4][4];
int player_dir[18];
int player_pos[18][2];

int pos[18][18][3];

int dx[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };

int simulate() { // 첫 번째 턴
	int px = player_pos[0][0] = 0;
	int py = player_pos[0][1] = 0;
	int result = board[0][0][0];
	player_dir[0] = pos[0][result][2];
	board[0][0][0] = -1;
	pos[0][result][0] = -1;
	for (int i = 1; i <= 16; ++i) {
		int x = pos[0][i][0];
		int y = pos[0][i][1];
		int d = pos[0][i][2];
		if (x < 0) continue;

		for (int j = 0; j < 8; ++j) {
			int nx = x + dx[d];
			int ny = y + dy[d];
			if (nx >= 0 && nx <= 3 && ny >= 0 && ny <= 3) {
				if (nx != px || ny != py) { // 이동 가능
					if (board[0][nx][ny]) {
						int other = board[0][nx][ny];
						pos[0][other][0] = x;
						pos[0][other][1] = y;

						pos[0][i][0] = nx;
						pos[0][i][1] = ny;
						pos[0][i][2] = d;

						board[0][x][y] = other;
						board[0][nx][ny] = i;
					}
					else {
						pos[0][i][0] = nx;
						pos[0][i][1] = ny;
						pos[0][i][2] = d;
						board[0][x][y] = 0;
						board[0][nx][ny] = i;
					}
					break;
				}
			}
			d += 1;
			if (d > 8) d = 1;
		}
	}
	return result;
}

int simulate(int t, int k) { // k칸 이동
	int result = 0;
	int px = player_pos[t][0];
	int py = player_pos[t][1];
	int pd = player_dir[t];
	int pnx = px + dx[pd] * k;
	int pny = py + dy[pd] * k;
	std::cout << pd << ' ' << px << ' ' << py << ' ' << pnx << ' ' << pny << '\n';
	if (pnx < 0 || pnx > 3 || pny < 0 || pny > 3) return 0; // 격자를 벗어남
	if (!board[t][pnx][pny]) return 0; // 도둑말 없음
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			board[t + 1][i][j] = board[t][i][j];
	board[t + 1][px][py] = 0;
	board[t + 1][pnx][pny] = -1;
	result = board[t][pnx][pny]; // get score
	player_pos[t + 1][0] = pnx;
	player_pos[t + 1][1] = pny;
	player_dir[t + 1] = pos[t][result][2];

	for (int i = 1; i <= 16; ++i) {
		pos[t + 1][i][0] = pos[t][i][0];
		pos[t + 1][i][1] = pos[t][i][1];
		pos[t + 1][i][2] = pos[t][i][2];
	}
	pos[t + 1][result][0] = -1;

	for (int i = 1; i <= 16; ++i) {
		int x = pos[t + 1][i][0];
		int y = pos[t + 1][i][1];
		int d = pos[t + 1][i][2];
		if (x < 0) continue;

		for (int j = 0; j < 8; ++j) {
			int nx = x + dx[d];
			int ny = y + dy[d];
			if (nx >= 0 && nx <= 3 && ny >= 0 && ny <= 3) {
				if (nx != pnx || ny != pny) { // 이동 가능
					if (board[t + 1][nx][ny]) {
						int other = board[t + 1][nx][ny];
						pos[t + 1][other][0] = x;
						pos[t + 1][other][1] = y;

						pos[t + 1][i][0] = nx;
						pos[t + 1][i][1] = ny;
						pos[t + 1][i][2] = d;

						board[t + 1][x][y] = other;
						board[t + 1][nx][ny] = i;
					}
					else {
						pos[t + 1][i][0] = nx;
						pos[t + 1][i][1] = ny;
						pos[t + 1][i][2] = d;
						board[t + 1][x][y] = 0;
						board[t + 1][nx][ny] = i;
					}
					break;
				}
			}
			d += 1;
			if (d > 8) d = 1;
		}
	}
	std::cout << result << '\n';
	return result;
}

int dfs(int depth) {
	// std::cout << depth << '\n';
	int result = 0;

	for (int i = 1; i < 4; ++i) {
		int score = simulate(depth, i);
		if (!score) continue;
		score += dfs(depth + 1);
		if (score > result)
			result = score;
	}
	return result;
}


int main() {
	freopen("input.txt", "r", stdin);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0, n, d; j < 4; ++j) {
			std::cin >> n >> d;
			board[0][i][j] = n;
			pos[0][n][0] = i;
			pos[0][n][1] = j;
			pos[0][n][2] = d;
		}
	}
	int cur = simulate();

	int max = dfs(0);

	std::cout << cur + max;

	return 0;
}