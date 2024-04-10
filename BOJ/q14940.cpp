#include <iostream>
#include <queue>

const int LEN = 1000;
const int dx[] = { 0, 0, 1, -1 };
const int dy[] = { 1, -1, 0, 0 };

int N, M, x, y, A[LEN][LEN], C[LEN][LEN];
std::queue<int> q;

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			std::cin >> A[i][j];
			if (A[i][j] == 2)
				q.push(i * M + j);
			if (A[i][j] == 1) C[i][j] = -1;
		}
	}
	while (q.size()) {
		x = q.front() / M;
		y = q.front() % M;
		q.pop();
		for (int d = 0, nx, ny; d < 4; ++d) {
			nx = x + dx[d];
			ny = y + dy[d];
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			if (A[nx][ny] != 1) continue;
			if (~C[nx][ny]) continue;
			C[nx][ny] = C[x][y] + 1;
			q.push(nx * M + ny);
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j)
			std::cout << C[i][j] << ' ';
		std::cout << '\n';
	}
}