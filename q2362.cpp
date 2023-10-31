#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

typedef long long ll;
const ll INF = 2e17;
const ll MOD = 1e9 + 7;
const int MAX = 20010;
const int OUT = 10000;

int N, K, source = 0, sink = MAX - 1;
std::string map[100];
std::map<int, ll> c[MAX], f[MAX];
int work[MAX], level[MAX];
std::vector<int> A[MAX];
int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };

bool bfs(int S, int T) {
	std::fill(level, level + MAX, -1);
	level[S] = 0;

	std::queue<int> q;
	q.push(S);

	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (const int& v : A[u]) {
			if (!~level[v] && c[u][v] - f[u][v] > 0) {
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}
	return ~level[T];
}

int dfs(int u, int T, ll flow) {
	if (u == T) return flow;

	for (int& i = work[u]; i < A[u].size(); ++i) {
		int v = A[u][i];

		if (level[v] == level[u] + 1 && c[u][v] - f[u][v] > 0) {
			int ret = dfs(v, T, std::min(c[u][v] - f[u][v], flow));

			if (ret > 0) {
				f[u][v] += ret;
				f[v][u] -= ret;
				return ret;
			}
		}
	}
	return 0;
}

ll dinic(int S, int T) {
	ll totalFlow = 0;

	while (bfs(S, T)) {
		std::fill(work, work + MAX, 0);

		while (1) {
			ll flow = dfs(S, T, INF);
			if (flow == 0)
				break;
			totalFlow += flow;
		}
	}

	return totalFlow;
}

// max flow

int main() {
	std::cin >> N >> K;

	for (int i = 0; i < N; ++i) std::cin >> map[i];

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (map[i][j] == 'X') {
				for (int d = 0, nx, ny; d < 4; ++d) {
					nx = i + dx[d]; ny = j + dy[d];
					if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
					if (map[nx][ny] == 'O') {
						std::cout << "No";
						return 0;
					}
				}
			}
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			char k = map[i][j];
			if (k == '+') continue;
			int node = i * N + j + 1;

			A[node + OUT].push_back(node);
			A[node].push_back(node + OUT);
			c[node + OUT][node] = 0;
			c[node][node + OUT] = 1;
			f[node + OUT][node] = 0;
			f[node][node + OUT] = 0;
			if (k == 'X') {
				A[source].push_back(node + OUT);
				c[source][node + OUT] = INF;
				f[source][node + OUT] = 0;
			}
			if (k == 'O') {
				A[node].push_back(sink);
				c[node][sink] = INF;
				f[node][sink] = 0;
			}

			for (int d = 0; d < 4; ++d) {
				int di = i + dx[d], dj = j + dy[d];
				int dn = N * dx[d] + dy[d];

				if (di < 0 || di >= N || dj < 0 || dj >= N) continue;

				if (map[di][dj] != '+') {
					A[node + OUT].push_back(node + dn);
					A[node + dn].push_back(node + OUT);
					c[node + dn][node + OUT] = 0;
					c[node + OUT][node + dn] = 1;
					f[node + dn][node + OUT] = 0;
					f[node + OUT][node + dn] = 0;

					A[node + dn + OUT].push_back(node);
					A[node].push_back(node + dn + OUT);
					c[node][node + dn + OUT] = 0;
					c[node + dn + OUT][node] = 1;
					f[node][node + dn + OUT] = 0;
					f[node + dn + OUT][node] = 0;
				}
			}
		}
	}

	ll result = dinic(source, sink);
	if (result <= K) std::cout << "Yes\n" << result;
	else std::cout << "No";
}