#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

typedef long long ll;
const ll INF = 2e17;
const int MAX = 401;
const int OUT = 200;

int N, M, U, V, source, sink;
ll c[MAX][MAX], f[MAX][MAX];
int work[MAX], level[MAX];
std::vector<int> A[MAX];
std::vector<int> result;

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

void bfs_track(int S) {
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
	for (int i = 1; i <= N; ++i) {
		if (~level[i] && !~level[i + OUT])
			result.push_back(i);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	std::cin >> source >> sink;
	sink += OUT;

	for (int i = 1; i <= N; ++i) {
		std::cin >> c[i][i + OUT];
		A[i + OUT].push_back(i);
		A[i].push_back(i + OUT);
	}
	while (M--) {
		std::cin >> U >> V;

		A[U + OUT].push_back(V);
		A[V].push_back(U + OUT);
		c[U + OUT][V] = INF;

		A[V + OUT].push_back(U);
		A[U].push_back(V + OUT);
		c[V + OUT][U] = INF;
	}
	ll f = dinic(source, sink);
	// std::cout << "max flow: " << f << '\n';
	bfs_track(source);
	for (const int& e : result) std::cout << e << ' ';
}