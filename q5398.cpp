#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <string>

const int INF = 1e9 + 7;
const int LEN = 501;
int u_len, v_len;
int U[LEN]; // pair of u(left side) u->v. 0 if u does not have any pair
int V[LEN]; // pair of v(right side) v->u. 0 if v does not have any pair
int D[LEN]; // distance of left side vertices
std::vector<int> graph[LEN];

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

struct Pos { int x, y; } pH[501], pV[501];
std::string wH[501], wV[501];

int solve() {
	std::cin >> u_len >> v_len;
	for (int i = 1; i <= u_len; ++i) graph[i].clear();
	for (int i = 1; i <= u_len; ++i) std::cin >> pH[i].y >> pH[i].x >> wH[i];
	for (int i = 1; i <= v_len; ++i) std::cin >> pV[i].y >> pV[i].x >> wV[i];
	for (int i = 1; i <= u_len; ++i) {
		for (int j = 1; j <= v_len; ++j) {
			if (pH[i].x >= pV[j].x && pH[i].x < pV[j].x + wV[j].length() &&
				pV[j].y >= pH[i].y && pV[j].y < pH[i].y + wH[i].length() &&
				wH[i][pV[j].y - pH[i].y] != wV[j][pH[i].x - pV[j].x]
				) graph[i].push_back(j);
		}
	}
	return u_len + v_len - hopcroft_karp();
}

int T;
int main() {
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';
}