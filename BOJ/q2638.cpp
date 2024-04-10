#include <iostream>
#include <queue>
#include <cstring>

typedef std::pair<int, int> pii;

bool map[100][100];
int visited[100][100];
int N, M;

void bfs() {
	std::queue<pii> q;
	memset(visited, 0, sizeof visited);
	q.push({ 0, 0 });
	visited[0][0] = 1;

	while (!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();

		if (x > 0) {
			if (map[x - 1][y]) visited[x - 1][y]++;
			if (!map[x - 1][y] && !visited[x - 1][y]) {
				visited[x - 1][y] = 1;
				q.push({ x - 1, y });
			}
		}
		if (x < N - 1) {
			if (map[x + 1][y]) visited[x + 1][y]++;
			if (!map[x + 1][y] && !visited[x + 1][y]) {
				visited[x + 1][y] = 1;
				q.push({ x + 1, y });
			}
		}
		if (y > 0) {
			if (map[x][y - 1]) visited[x][y - 1]++;
			if (!map[x][y - 1] && !visited[x][y - 1]) {
				visited[x][y - 1] = 1;
				q.push({ x, y - 1 });
			}
		}
		if (y < M - 1) {
			if (map[x][y + 1]) visited[x][y + 1]++;
			if (!map[x][y + 1] && !visited[x][y + 1]) {
				visited[x][y + 1] = 1;
				q.push({ x, y + 1 });
			}
		}
	}
}
int melt() {
	int count = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (visited[i][j] > 1) {
				++count;
				map[i][j] = false;
			}
		}
	}
	return count;
}
bool simulate() {
	bfs();
	return melt();
}

int main() {
	int time = 0;
	std::cin >> N >> M;

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			std::cin >> map[i][j];
	
	while (simulate()) ++time;

	std::cout << time;
}