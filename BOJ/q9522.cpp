#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int INF = 1e9 + 7;
const int LEN = 501;
int u_len, v_len;
int U[LEN]; // pair of u(left side) u->v. 0 if u does not have any pair
int V[LEN]; // pair of v(right side) v->u. 0 if v does not have any pair
int D[LEN]; // distance of left side vertices
std::vector<int> graph[LEN];

bool bfs() {
	std::queue<int> q;
	for (int u = 1; u < LEN; ++u) {
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
		for (int u = 1; u < LEN; ++u)
			if (!U[u] && dfs(u))
				++result;
	}
	return result;
}

int N, M;
bool row[LEN], col[LEN];

int main() {
	std::cin >> N;
	for (int i = 0, u, v; i < N; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		if (!row[u]) { row[u] = 1; ++u_len; }
		if (!col[v]) { col[v] = 1; ++v_len; }
	}
	M = hopcroft_karp();
	std::cout << (u_len == M && v_len == M ? "Slavko" : "Mirko");
}