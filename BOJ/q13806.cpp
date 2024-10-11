#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

const int INF = 1e9;
const int LEN = 1001;

int N, M, L;
int g[100][100];
int p[LEN], t[LEN];

int U[LEN]; // pair of u(left side) u->v. 0 if u does not have any pair
int V[LEN]; // pair of v(right side) v->u. 0 if v does not have any pair
int D[LEN]; // distance of left side vertices
std::vector<int> graph[LEN];

bool bfs() {
	std::queue<int> q;
	for (int u = 1; u <= L; ++u) {
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
		for (int u = 1; u <= L; ++u)
			if (!U[u] && dfs(u))
				++result;
	}
	return result;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	while (1) {
		std::cin >> N >> M >> L;
		if (!N && !M && !L) break;
		for (int i = 1; i <= L; ++i) graph[i].clear();

		// get min dist
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				g[i][j] = i == j ? 0 : INF;
		for (int i = 0, u, v, d; i < M; ++i) {
			std::cin >> u >> v >> d;
			g[u][v] = g[v][u] = d;
		}
		for (int k = 0; k < N; ++k)
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < N; ++j)
					g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);

		// get matching
		for (int i = 1; i <= L; ++i) std::cin >> p[i] >> t[i];
		for (int i = 1; i <= L; ++i) {
			for (int j = 1; j <= L; ++j) {
				if (i == j) continue;
				if (t[i] + g[p[i]][p[j]] <= t[j]) graph[i].push_back(j);
			}
		}
		std::cout << L - hopcroft_karp() << '\n';
	}
}