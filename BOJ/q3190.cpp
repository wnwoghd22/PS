#include <iostream>
#include <deque>

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { 1, 0, -1, 0 };

int map[100][100];
int command[10300];

int N, K, L;
int d;
char c;

std::deque<int> dq;

int main() {
	std::cin >> N >> K;
	for (int i = 0, r, c; i < K; ++i) {
		std::cin >> r >> c;
		map[r - 1][c - 1] = 2;
	}
	std::cin >> L;
	for (int i = 0, x; i < L; ++i) {
		std::cin >> x >> c;
		command[x] = c == 'L' ? -1 : 1;
	}

	int x = 0, y = 0, z;
	dq.push_front(0);
	map[0][0] = 1;
	int t;
	for (t = 1; t < 10300; ++t) {
		x += dx[d], y += dy[d];
		if (x < 0 || x >= N || y < 0 || y >= N) break;
		if (map[x][y] == 1) break;
		if (map[x][y] != 2) {
			z = dq.back(); dq.pop_back();
			map[z / N][z % N] = 0;
		}
		map[x][y] = 1;
		dq.push_front(x * N + y);
		d = (d + command[t] + 4) % 4;
	}
	std::cout << t;
}