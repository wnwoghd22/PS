#include <iostream>
#include <vector>

const int LEN = 1'001;
const int dx[4] = { 0, 1, 0, -1 };
const int dy[4] = { 1, 0, -1, 0 };

int T, C, R;
std::vector<int> g[LEN * LEN];
char S[LEN][LEN];
int root = -1;
int tip, max;

void dfs(int u, int p = -1, int dist = 0) {
	if (max < dist) tip = u, max = dist;

	for (const int& v : g[u]) {
		if (v != p)
			dfs(v, u, dist + 1);
	}
}

void make_tree() {
	for (int i = 1; i < C - 1; ++i) {
		for (int j = 1; j < R - 1; ++j) {
			int u = i * C + j;
			if (S[i][j] == '.') root = u;
			else continue;
			for (int d = 0; d < 4; ++d) {
				int nx = i + dx[d];
				int ny = j + dy[d];
				int v = nx * C + ny;
				if (S[nx][ny] == '.') {
					g[u].push_back(v);
				}
			}
		}
	}
}

int solve() {
	std::cin >> R >> C;
	for (int i = 0; i < C; ++i) std::cin >> S[i];
	for (int i = 0; i < R * C; ++i) g[i].clear();
	make_tree();
	max = -1; dfs(root);
	max = -1; dfs(tip);
	return max;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) std::cout << "Maximum rope length is " << solve() << ".\n";
}