#include <fstream>
#include <iostream>

using namespace std;

char map[101][101];
int pathLen = 4000;

int dx[] = { 0, 1, -1, 0 };
int dy[] = { -1, 0, 0, 1 };

bool isIsolated(int x, int y, int prevx, int prevy) {
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 1 || ny < 1 || nx > 98 || ny > 98) continue;
		if (nx == prevx && ny == prevy) continue;
		if (map[nx][ny] == '.') return false;
	}
	return true;
}

void dfs(int x, int y, const int depth = 1) {
	static bool finded = false;

	if (depth > pathLen) finded = true;

	cout << depth << '\n';

	map[x][y] = '.';

	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 1 || ny < 1 || nx > 98 || ny > 98) continue;
		if (map[nx][ny] == 'X') continue;
		if (!finded && map[nx][ny] == '#' && isIsolated(nx, ny, x, y)) {
			dfs(nx, ny, depth + 1);
		}
	}

	if (!finded) map[x][y] = '#';
}

int main()
{
	string rawFilePath = "path5.txt";
	string filePath = "path.txt";

	ifstream openFile(rawFilePath.data());
	ofstream writeFile(filePath.data());

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
	
	cout << "len?: ";
	cin >> pathLen;
	cout << "\nfind path " << pathLen << ":\n";

	dfs(19, 59);

	if (writeFile.is_open()) {
		for (int i = 0; i < 100; ++i) {
			cout << map[i] << '\n';
			writeFile << map[i] << '\n';
		}
		writeFile.close();
	}

	return 0;
}