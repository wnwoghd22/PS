#include <iostream>
#include <vector>

int N, map[12][12];

int pos[12][2];
bool adj[12], accessable[12][4];
int dx[] = { -1, 0, 1, 0 }, dy[] = { 0, 1, 0, -1 };

int cores, max_cores = 0, min_cost = 1e9;

void dfs(int accessed, int cost, int i) {
	if (i == cores) {
		if (accessed > max_cores) {
			max_cores = accessed;
			min_cost = cost;
		}
		else if (accessed == max_cores) {
			min_cost = std::min(min_cost, cost);
		}
		return;
	}
	if (adj[i]) {
		dfs(accessed + 1, cost, i + 1);
		return;
	}
	for (int d = 0; d < 4; ++d) {
		if (accessable[i][d]) {
			int flag = true;
			int cadd = 0;
			int x = pos[i][0];
			int y = pos[i][1];
			int nx = x, ny = y;
			while (nx > 0 && nx < N - 1 && ny > 0 && ny < N - 1) {
				nx += dx[d]; ny += dy[d];
				++cadd;
				if (map[nx][ny]) {
					flag = false;
					break;
				}
				map[nx][ny] = true;
			}
			if (flag) dfs(accessed + 1, cost + cadd, i + 1);
			nx = x; ny = y;
			for (int idx = 0; idx < cadd - !flag; ++idx) { // !flag: is blocked, must not erase others.
				nx += dx[d]; ny += dy[d];
				map[nx][ny] = false;
			}
		}
	}
	dfs(accessed, cost, i + 1);
}


int solve() {
	cores = 0, max_cores = 0, min_cost = 1e9;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> map[i][j];
			if (map[i][j]) {
				adj[cores] = i == 0 || i == N - 1 || j == 0 || j == N - 1;
				if (!adj[cores])
					pos[cores][0] = i, pos[cores][1] = j;
				cores += 1;
			}
		}
	}
	for (int idx = 0; idx < cores; ++idx) {
		if (adj[idx]) continue;
		int x = pos[idx][0];
		int y = pos[idx][1];

		for (int i = 0; i < 4; ++i) {
			int nx = x, ny = y;
			bool flag = true;
			while (nx > 0 && nx < N - 1 && ny > 0 && ny < N - 1) {
				nx += dx[i]; ny += dy[i];
				if (map[nx][ny]) {
					flag = false;
					break;
				}
			}
			accessable[idx][i] = flag;
		}
	}

	dfs(0, 0, 0);

	return min_cost;
}

int main() {
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; ++t) {
		std::cout << '#' << t << ' ' << solve() << '\n';
	}
}