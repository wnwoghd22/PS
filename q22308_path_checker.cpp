#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

char map[101][101];
bool visited[101][101];
int pathLen = 4000;

int dx[] = { 0, 1, -1, 0 };
int dy[] = { -1, 0, 0, 1 };

void bfs(int x, int y) {
	std::queue<std::pair<int, std::pair<int, int>>> q;
	
	q.push({ 1, {x, y} });
	visited[x][y] = true;

	while (!q.empty()) {
		int depth = q.front().first;
		x = q.front().second.first;
		y = q.front().second.second;
		q.pop();

		cout << depth << '\n';

		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 1 || ny < 1 || nx > 98 || ny > 98) continue;
			if (!visited[nx][ny] && map[nx][ny] == '.') {
				visited[nx][ny] = true;
				q.push({ depth + 1, {nx, ny} });
			}
		}
	}
}

int main()
{
	string filePath = "path5.txt";

	ifstream openFile(filePath.data());

	int lineNum = 0;
	int count = 0;
	int obstacles = 0;

	if (openFile.is_open()) {
		std::cout << "open" << '\n';

		for (int i = 0; i < 100; ++i) {
			openFile.getline(map[i], 101);
			cout << map[i] << '\n';
		}
		openFile.close();
	}

	bfs(1, 1);

	return 0;
}