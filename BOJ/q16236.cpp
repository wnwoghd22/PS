#include <iostream>
#include <queue>
#include <cstring>

const int MAX = 20;
int map[MAX][MAX];
int N;
int level, _exp;

/// <summary>
/// 
/// </summary>
/// <param name="x">X 좌표. 변경 우려 있음</param>
/// <param name="y">Y 좌표. 변경 우려 있음</param>
/// <returns>최단 거리</returns>
int dfs(int& x, int& y, const int level) {
	static int visited[MAX][MAX];
	static std::queue<std::pair<int, std::pair<int, int>>> q;
	static std::priority_queue<std::pair<int, std::pair<int, int>>> pq;
	memset(visited, 0, sizeof visited);
	while (!q.empty()) q.pop();
	while (!pq.empty()) pq.pop();

	int distance;
	visited[x][y] = true;
	q.push({ 0, { x, y } });
	
	while (!q.empty()) {
		distance = q.front().first;
		x = q.front().second.first; y = q.front().second.second; q.pop();
		if (map[x][y] && map[x][y] < level) {
			pq.push({ -distance, { -x, -y } });
		}

		if (x > 0 && !visited[x - 1][y] && map[x - 1][y] <= level) {
			visited[x - 1][y] = true;
			q.push({ distance + 1, {x - 1, y} });
		}
		if (y > 0 && !visited[x][y - 1] && map[x][y - 1] <= level) {
			visited[x][y - 1] = true;
			q.push({ distance + 1, {x, y - 1} });
		}
		if (y < N - 1 && !visited[x][y + 1] && map[x][y + 1] <= level) {
			visited[x][y + 1] = true;
			q.push({ distance + 1, {x, y + 1} });
		}
		if (x < N - 1 && !visited[x + 1][y] && map[x + 1][y] <= level) {
			visited[x + 1][y] = true;
			q.push({ distance + 1, {x + 1, y} });
		}
	}
	if (!pq.empty()) {
		distance = -pq.top().first;
		x = -pq.top().second.first; y = -pq.top().second.second;
		map[x][y] = 0;
		return distance;
	}

	return -1;
}

int main() {
	std::cin >> N;
	level = 2; _exp = 0;
	int posX, posY, time = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> map[i][j];
			if (map[i][j] == 9) {
				posX = i, posY = j, map[i][j] = 0;
			}
		}
	}
	while (true) {
		std::cout << "level: " << level << " exp: " << _exp << " x: " << posX << " y: " << posY << " time: " << time << '\n';
		int current = dfs(posX, posY, level);
		if (current == -1) break;
		time += current;
		++_exp;
		if (_exp == level) ++level, _exp = 0;
	}
	std::cout << time;
}