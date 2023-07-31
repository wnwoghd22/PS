#include <iostream>
#include <queue>

const int LEN = 500;
const int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };

int map[LEN][LEN];

struct P { 
	int x, y;
	bool operator<(const P& r) const {
		return map[x][y] > map[r.x][r.y];
	}
};
std::priority_queue<P> pq;

int N, dp[LEN][LEN];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> map[i][j];
			pq.push({ i, j });
		}
	}
	while (pq.size()) {
		auto [x, y] = pq.top(); pq.pop();
		for (int d = 0, nx, ny; d < 4; ++d) {
			nx = x + dx[d];
			ny = y + dy[d];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N || map[nx][ny] <= map[x][y]) continue;
			dp[nx][ny] = std::max(dp[nx][ny], dp[x][y] + 1);
		}
	}
	int max = 0;

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			max = std::max(max, dp[i][j]);
	std::cout << max + 1;
}