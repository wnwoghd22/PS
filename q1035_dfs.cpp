#include <iostream>
#include <algorithm>
#include <cstring>

const int INF = 1e9;

int N;

int cost[5][5];

int dp[5][1 << 5];
int f(int i, int b) {
	if (i == N) return 0;
	int& ref = dp[i][b];
	if (~ref) return ref;
	ref = INF;
	for (int j = 0; j < N; ++j) {
		if (b & 1 << j) continue;
		ref = std::min(ref, f(i + 1, b | 1 << j) + cost[i][j]);
	}
	return ref;
}

char map[5][6];
int posX[5], posY[5];

int min = INF;

bool checked[5][5];
bool visited[5][5];
int tX[5], tY[5];
int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };
int dfs(int i) {
	int x = i / 5, y = i % 5;
	visited[x][y] = 1;
	int s = 1;
	for (int d = 0, nx, ny; d < 4; ++d) {
		nx = x + dx[d], ny = y + dy[d];
		if (nx >= 0 && nx < 5 && ny >= 0 && ny < 5 && checked[nx][ny] && !visited[nx][ny]) {
			s += dfs(nx * 5 + ny);
		}
	}
	return s;
}

void dfs(int d, int i) {
	if (d == N) {
		if (dfs(tX[0] * 5 + tY[0]) == N) {
			memset(dp, -1, sizeof dp);
			min = std::min(min, f(0, 0));
		}
		for (int j = 0; j < N; ++j) visited[tX[j]][tY[j]] = 0;
		return;
	}
	if (i == 25) return;

	dfs(d, i + 1);

	int x = i / 5, y = i % 5;
	tX[d] = x; tY[d] = y;
	checked[x][y] = 1;
	for (int j = 0; j < N; ++j) {
		cost[d][j] = abs(x - posX[j]) + abs(y - posY[j]);
	}

	dfs(d + 1, i + 1);
	checked[x][y] = 0;
}

int main() {
	for (int i = 0; i < 5; ++i) {
		std::cin >> map[i];
		for (int j = 0; j < 5; ++j) {
			if (map[i][j] == '*') {
				posX[N] = i;
				posY[N] = j;
				++N;
			}
		}
	}
	dfs(0, 0);

	std::cout << min;
}