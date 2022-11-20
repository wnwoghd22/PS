#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

typedef std::pair<int, int> pii;

int map[3000][3000];
int N, M, K, r, c, d;
std::queue<std::pair<pii, int>> qj;
const int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };

void bfs_jam() {
	while (!qj.empty()) {
		const auto& pos = qj.front(); qj.pop();
		if (pos.second == 1) continue;
		int jam = pos.second - 1;
		for (int i = 0; i < 4; ++i) {
			int dr = pos.first.first + dx[i], dc = pos.first.second + dy[i];
			if (dr < 0 || dr >= N || dc < 0 || dc >= M) continue;
			if (jam > map[dr][dc]) {
				map[dr][dc] = jam;
				if (jam > 1) qj.push({ {dr, dc}, jam });
			}
		}
	}
}

int bfs() {
	std::queue<std::pair<pii, int>> q;
	q.push({ {0, 0}, 0 });
	map[0][0] = 1;
	while (!q.empty()) {
		const auto& pos = q.front(); q.pop();
		if (pos.first.first == N - 1 && pos.first.second == M - 1) return pos.second;
		for (int i = 0; i < 4; ++i) {
			int dr = pos.first.first + dx[i], dc = pos.first.second + dy[i];
			if (dr < 0 || dr >= N || dc < 0 || dc >= M) continue;
			if (!map[dr][dc]) {
				map[dr][dc] = 1;
				q.push({ {dr, dc}, pos.second + 1 });
			}
		}
	}

	return -1;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M >> K;
	while (K--) {
		std::cin >> r >> c >> d;
		map[r - 1][c - 1] = d + 1;
		if (d == 0) continue;
		qj.push({ {r - 1, c - 1}, d + 1 });
	}
	bfs_jam();
	int result = bfs();

	if (~result) std::cout << "YES\n" << result;
	else std::cout << "NO";
}