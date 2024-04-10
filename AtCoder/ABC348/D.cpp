#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

const int LEN = 201;
const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

int H, W, N;
char map[LEN][LEN];
int A[LEN][LEN];
int visited[LEN][LEN];

struct Info { int r, c, e; };
std::vector<Info> arr;

int bfs(int r, int c, const int e) {
	std::queue<int> q;
	memset(visited, -1, sizeof visited);
	visited[r][c] = e;
	q.push(r * W + c);
	while (q.size()) {
		r = q.front() / W;
		c = q.front() % W;
		q.pop();
		for (int d = 0; d < 4; ++d) {
			int nr = r + dx[d];
			int nc = c + dy[d];
			if (nr < 0 || nr >= H || nc < 0 || nc >= W) continue;
			if (~visited[nr][nc]) continue;
			if (map[nr][nc] == '#') continue;
			if (map[nr][nc] == 'T') return 1;
			visited[nr][nc] = visited[r][c] - 1;
			if (visited[nr][nc]) q.push(nr * W + nc);
			if (A[nr][nc]) {
				arr.push_back({ nr, nc, A[nr][nc] });
				A[nr][nc] = 0;
			}
		}
	}
	return 0;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> H >> W;
	int sr, sc;
	for (int i = 0; i < H; ++i) {
		std::cin >> map[i];
		for (int j = 0; j < W; ++j) {
			if (map[i][j] == 'S') {
				sr = i; sc = j;
			}
		}
	}
	std::cin >> N;
	for (int i = 0, r, c, e; i < N; ++i) {
		std::cin >> r >> c >> e;
		A[r - 1][c - 1] = e;
	}
	if (A[sr][sc]) {
		arr.push_back({ sr, sc, A[sr][sc] });
		A[sr][sc] = 0;
	}
	while (arr.size()) {
		Info cur = arr.back();
		arr.pop_back();
		if (bfs(cur.r, cur.c, cur.e)) {
			std::cout << "Yes";
			return 0;
		}
	}
	std::cout << "No";
}