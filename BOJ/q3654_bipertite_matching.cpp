#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int INF = 1e9 + 7;
const int LEN = 250'001;
int T, N, M;
int u_len, v_len;
int U[LEN]; // pair of u(left side) u->v. 0 if u does not have any pair
int V[LEN]; // pair of v(right side) v->u. 0 if v does not have any pair
int D[LEN]; // distance of left side vertices
std::vector<int> graph[LEN];
char map[500][501];
int idx[500][500];

bool bfs() {
	std::queue<int> q;
	for (int u = 1; u <= u_len; ++u) {
		if (!U[u]) { // free vertex
			D[u] = 0;
			q.push(u);
		}
		else D[u] = INF;
	}
	D[0] = INF;

	while (q.size()) {
		int u = q.front(); q.pop();

		if (D[u] < D[0]) {
			for (const int& v : graph[u]) {
				if (D[V[v]] == INF) { // v is not considered so far
					D[V[v]] = D[u] + 1;
					q.push(V[v]);
				}
			}
		}
	}
	return D[0] != INF; // if could come back to NIL using alternating path then there is an augmenting path
}

bool dfs(int u) {
	if (u) {
		for (const int& v : graph[u]) {
			if (D[V[v]] == D[u] + 1) {
				if (dfs(V[v])) {
					V[v] = u;
					U[u] = v;
					return true;
				}
			}
		}
		D[u] = INF;
		return false;
	}
	return true;
}

int hopcroft_karp() {
	memset(U, 0, sizeof U);
	memset(V, 0, sizeof V);
	int result = 0;

	while (bfs()) {
		for (int u = 1; u <= u_len; ++u)
			if (!U[u] && dfs(u))
				++result;
	}
	return result;
}

void solve() {
	memset(idx, 0, sizeof idx);
	int matching[2] = { 0, 0 };
	int b = 0, w = 0;

	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		std::cin >> map[i];
		for (int j = 0; j < M; ++j) {
			if (map[i][j] == 'W') ++w;
			if (map[i][j] == 'B') idx[i][j] = u_len = ++b;
		}
	}
	if (w != b << 1) {
		std::cout << "NO\n";
		return;
	}

	for (int k = 0; k < 2; ++k) {
		v_len = 0;
		for (std::vector<int>& v : graph) v.clear();
		for (int i = k; i < N; i += 2) {
			for (int j = 0; j < M; ++j) {
				if (map[i][j] == 'W') {
					++v_len;
					for (int d = 0, dx = 0, dy = 1, nx, ny; d < 4; ++d, nx = dx, dx = -dy, dy = nx) {
						nx = i + dx, ny = j + dy;
						if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
						if (map[nx][ny] == 'B')
							graph[idx[nx][ny]].push_back(v_len);
					}
				}
			}
		}
		matching[k] = hopcroft_karp();
	}
	if (matching[0] + matching[1] == b << 1) std::cout << "YES\n";
	else std::cout << "NO\n";
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) solve();
}