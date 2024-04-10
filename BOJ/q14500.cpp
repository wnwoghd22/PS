#include <iostream>
#include <algorithm>

int map[500][500];
int visited[500][500];
int N, M;

int dfs(int x, int y, int depth = 1) {
	int weight = map[x][y], delta = 0;

	if (depth == 4) return weight;

	visited[x][y] = true;

	if (x > 0 && !visited[x - 1][y]) delta = std::max(delta, dfs(x - 1, y, depth + 1));
	if (x < N - 1 && !visited[x + 1][y]) delta = std::max(delta, dfs(x + 1, y, depth + 1));

	if (y > 0 && !visited[x][y - 1]) delta = std::max(delta, dfs(x, y - 1, depth + 1));
	if (y < M - 1 && !visited[x][y + 1]) delta = std::max(delta, dfs(x, y + 1, depth + 1));
	
	visited[x][y] = false;

	return weight + delta;
}
int fuck(int x, int y) {
	int result = 0;

	if (x > 0 && x < N - 1 && y > 0) // で
		result = std::max(result, map[x][y] + map[x - 1][y] + map[x + 1][y] + map[x][y - 1]);
	if (x > 0 && x < N - 1 && y < M - 1) // ぬ
		result = std::max(result, map[x][y] + map[x - 1][y] + map[x + 1][y] + map[x][y + 1]);

	if (y > 0 && y < N - 1 && x > 0) // っ
		result = std::max(result, map[x][y] + map[x][y - 1] + map[x][y + 1] + map[x - 1][y]);
	if (y > 0 && y < M - 1 && x < N - 1) // た
		result = std::max(result, map[x][y] + map[x][y - 1] + map[x][y + 1] + map[x + 1][y]);

	return result;
}

int main() {
	int result = 0;
	std::cin >> N >> M;

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			std::cin >> map[i][j];

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			result = std::max({ result, dfs(i, j), fuck(i, j) });

	std::cout << result;
}