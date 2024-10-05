#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

typedef std::pair<int, int> pii;
typedef std::pair<int, pii> ipi;
typedef std::pair<pii, int> ppi;

int map[3000][3000];
int N, M, K, r, c, d;
std::priority_queue<ipi> pq;
const int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };

void bfs_jam() {
	while (!pq.empty()) {
		ipi pos = pq.top(); pq.pop();
		if (pos.first == 1) continue;
		int jam = pos.first - 1;
		for (int i = 0; i < 4; ++i) {
			int dr = pos.second.first + dx[i], dc = pos.second.second + dy[i];
			if (dr < 0 || dr >= N || dc < 0 || dc >= M) continue;
			if (jam > map[dr][dc]) {
				map[dr][dc] = jam;
				if (jam > 1) pq.push({ jam, {dr, dc} });
			}
		}
	}
}

int bfs() {
	std::queue<ppi> q;
	q.push({ {0, 0}, 0 });
	map[0][0] = 1;
	while (!q.empty()) {
		ppi pos = q.front(); q.pop();
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
		pq.push({d + 1, {r - 1, c - 1}});
	}
	bfs_jam();

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j)
			std::cout << map[i][j] << ' ';
		std::cout << '\n';
	}

	int result = bfs();

	if (~result) std::cout << "YES\n" << result;
	else std::cout << "NO";
}