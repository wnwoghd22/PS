#include <iostream>
#include <queue>
#include <cstring>

const int LEN = 1502;
const int INF = 1e9;
char S[LEN];
bool map[LEN][LEN];
int sum[LEN][LEN]; // sum of obstacles
int sum_ld[LEN][LEN]; // connected with left-down
int sum_ru[LEN][LEN]; // connected with right-up
int W, H, L, X, Y;

int dx[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
int dy[] = { 1, 0, -1, 1, -1, 1, 0, -1 };
bool mask[LEN][LEN];

void bfs_mask(int x, int y, int arr[LEN][LEN]) {
	std::queue<int> q;
	memset(mask, 0, sizeof mask);

	q.push(x * (W + 2) + y);
	mask[x][y] = 1;
	while (q.size()) {
		x = q.front() / (W + 2);
		y = q.front() % (W + 2);
		q.pop();
		
		for (int d = 0, nx, ny; d < 8; ++d) {
			nx = x + dx[d], ny = y + dy[d];
			if (nx < 0 || nx > H + 1 || ny < 0 || ny > W + 1) continue;
			if (mask[nx][ny]) continue;
			mask[nx][ny] = 1;
			if (map[nx][ny])
				q.push(nx * (W + 2) + ny);
		}
	}
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j)
			arr[i][j] = arr[i - 1][j] + arr[i][j - 1] - arr[i - 1][j - 1] + mask[i][j];
	/*for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j)
			std::cout << arr[i][j] << ' ';
		std::cout << '\n';
	}*/
}

bool is_blocking(int x, int y, int l) {
	int ld = sum_ld[x + l][y + l] - sum_ld[x][y + l] - sum_ld[x + l][y] + sum_ld[x][y];
	int ru = sum_ru[x + l][y + l] - sum_ru[x][y + l] - sum_ru[x + l][y] + sum_ru[x][y];
	return ld && ru;
}

bool is_empty(int x, int y, int l) {
	int obs = sum[x + l][y + l] - sum[x][y + l] - sum[x + l][y] + sum[x][y];
	return !obs;
}

int _x, _y;
int binary_search(int x, int y) {
	int l = 1, r = std::min(W - y, H - x), m, result = INF;
	while (l <= r) {
		m = l + r >> 1;
		if (is_blocking(x, y, m)) {
			result = std::min(result, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	return result;
}
void check() {
	L = INF;
	for (int i = 0; i < H; ++i) {
		for (int j = !i; j < W; ++j) {
			int l = binary_search(i, j);
			if (i + l >= H && j + l >= W) continue;
			if (is_empty(i, j, l)) {
				if (l < L) {
					L = l;
					Y = i + 1;
					X = j + 1;
				}
			}
		}
	}
}

int main() {
	std::cin >> W >> H;
	map[0][W] = map[0][W + 1] = map[1][W + 1] = 1;
	map[H][0] = map[H + 1][0] = map[H + 1][1] = 1;
	for (int i = 2; i < W; ++i) map[0][i] = map[H + 1][i] = 1;
	for (int i = 2; i < H; ++i) map[i][0] = map[i][W + 1] = 1;
	for (int i = 1; i <= H; ++i) {
		std::cin >> S;
		for (int j = 1; j <= W; ++j) {
			map[i][j] = S[j - 1] == '#';
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + map[i][j];
		}
	}
	/*for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j)
			std::cout << sum[i][j] << ' ';
		std::cout << '\n';
	}*/

	bfs_mask(0, W + 1, sum_ru);
	bfs_mask(H + 1, 0, sum_ld);

	check();

	if (L == INF) std::cout << "Impossible";
	else std::cout << L << ' ' << X << ' ' << Y;
}