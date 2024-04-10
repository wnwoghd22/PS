#include <iostream>
#include <queue>
#include <cstring>

bool key[26], visited[100][100];
std::vector<std::pair<int, int>> locked[26];
std::string keys, map[100];
int T, h, w, dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 }, result = 0;
std::queue<std::pair<int, int>> q;

bool check_node(int i, int j) {
	if (i < 0 || i >= h || j < 0 || j >= w) return false;
	if (visited[i][j]) return false;
	char c = map[i][j];
	if (c == '*') return false;
	visited[i][j] = true;
	if (c >= 'A' && c <= 'Z') {
		if (key[c - 'A']) return true;
		else {
			locked[c - 'A'].push_back({ i, j });
			return false;
		}
	}
	if (c >= 'a' && c <= 'z') {
		if (!key[c - 'a']) {
			key[c - 'a'] = true;
			for (const auto& pos : locked[c - 'a']) {
				q.push(pos);
			}
		}
	}
	if (c == '$') result += 1;
	return true;
}

int bfs() {
	result = 0;
	q = std::queue<std::pair<int, int>>();
	for (int i = 0; i < w; ++i) {
		if (check_node(0, i)) q.push({ 0, i });
		if (check_node(h - 1, i)) q.push({ h - 1, i });
	}
	for (int i = 1; i < h - 1; ++i) {
		if (check_node(i, 0)) q.push({ i, 0 });
		if (check_node(i, w - 1)) q.push({ i, w - 1 });
	}

	while (!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			if (check_node(nx, ny)) {
				q.push({ nx, ny });
			}
		}
	}
	return result;
}

int solve() {
	memset(key, 0, sizeof key);
	memset(visited, 0, sizeof visited);
	for (auto& v : locked) v.clear();

	std::cin >> h >> w;
	for (int i = 0; i < h; ++i) std::cin >> map[i];
	std::cin >> keys;
	if (keys != "0") for (const char& c : keys) key[c - 'a'] = true;
	
	return bfs();
}

int main() {
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';
}