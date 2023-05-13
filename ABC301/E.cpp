#include <iostream>
#include <queue>
#include <cstring>

const int INF = 1e9 + 7;

char map[300][301];
int H, W, T, s[2], e[2], o[18][2], cnt;
int dist[20][20], di[4] = { 0, 0, 1, -1 }, dj[4] = { 1, -1, 0, 0 };

int visited[300][300];
void bfs(int x, int y, int u) {
	memset(visited, 0, sizeof visited);
	std::queue<int> q;
	visited[x][y] = 1;
	q.push({ x * W + y });
	while (q.size()) {
		int i = q.front() / W, j = q.front() % W;
		q.pop();

		for (int d = 0; d < 4; ++d) {
			int ni = i + di[d], nj = j + dj[d];
			if (ni < 0 || ni >= H || nj < 0 || nj >= W) continue;
			if (map[ni][nj] == '#') continue;
			if (visited[ni][nj]) continue;
			if (map[ni][nj] == 'G') {
				int v = 1;
				visited[ni][nj] = visited[i][j] + 1;
				dist[u][v] = visited[ni][nj] - 1;
				continue;
			}
			if (map[ni][nj] == 'o') {
				int v;
				for (int k = 0; k < cnt; ++k) {
					if (o[k][0] == ni && o[k][1] == nj) {
						v = k + 2;
						break;
					}
				}
				visited[ni][nj] = visited[i][j] + 1;
				dist[u][v] = visited[ni][nj] - 1;
			}
			visited[ni][nj] = visited[i][j] + 1;
			q.push({ ni * W + nj });
		}
	}
}

int max;
int dp[20][1 << 20];

int f(int i, int c, int dst, int bit) {
	int& ref = dp[i][bit];
	if (~ref) return ref;

	if (i == 1) { // destination
		max = std::max(max, c);
		return 0;
	}

	ref = INF;

	for (int j = 1; j < cnt + 2; ++j) {
		if (bit & (1 << j)) continue;
		if (!dist[i][j]) continue;
		if (dst + dist[i][j] > T) continue;
		int d = f(j, c + 1, dst + dist[i][j], bit | (1 << j)) + dist[i][j];
		ref = std::min(ref, d);
	}

	return ref;
}

int main() {
	std::cin >> H >> W >> T;
	for (int i = 0; i < H; ++i) std::cin >> map[i];
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (map[i][j] == 'S') s[0] = i, s[1] = j;
			if (map[i][j] == 'G') e[0] = i, e[1] = j;
			if (map[i][j] == 'o') o[cnt][0] = i, o[cnt][1] = j, ++cnt;
		}
	}
	bfs(s[0], s[1], 0);
	for (int i = 0; i < cnt; ++i)
		bfs(o[i][0], o[i][1], i + 2);

	/*for (int i = 0; i < cnt + 2; ++i) {
		for (int j = 0; j < cnt + 2; ++j)
			std::cout << dist[i][j] << ' ';
		std::cout << '\n';
	}*/

	if (dist[0][1] > T) std::cout << -1;
	else {
		memset(dp, -1, sizeof dp);
		f(0, -1, 0, 1);
		std::cout << max;
	}
}