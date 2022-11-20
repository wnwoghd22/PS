#include <iostream>
#include <vector>
#include <queue>

const int MAX = 2503;
const int INF = 1e9;
const int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };
const int table[6][6] = {
//  A  B  C  D     F
   10, 8, 7, 5, 0, 1, // A
	8, 6, 4, 3, 0, 1, // B
	7, 4, 3, 2, 0, 1, // C
	5, 3, 2, 2, 0, 1, // D
	0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 0, 0  // F
};

std::string map[50];
int c[MAX][MAX], f[MAX][MAX], d[MAX][MAX]; // capacity, flow, distance(cost)
std::vector<int> a[MAX]; // adjacent graph
int const source = 2501, sink = 2502;
int N, M;
bool inQ[MAX];
int p[MAX], dist[MAX];

std::pair<int, int> MCMF(int source, int sink) {
	int mc = 0, mf = 0;

	while (true) {
		std::queue<int> q;
		std::fill(inQ, inQ + MAX, false);
		std::fill(p, p + MAX, 0);
		std::fill(dist, dist + MAX, INF);

		dist[source] = 0;
		q.push(source);
		inQ[source] = true;

		while (!q.empty()) {
			int u = q.front(); q.pop(); inQ[u] = false;
			for (const int& v : a[u]) { // u -> v
				if (c[u][v] - f[u][v] > 0 && dist[u] + d[u][v] < dist[v]) {
					dist[v] = dist[u] + d[u][v];
					p[v] = u;
					if (!inQ[v]) {
						inQ[v] = true;
						q.push(v), inQ[v] = true;
					}
				}
			}
		}
		if (!p[sink]) break;

		int flow = INF;

		for (int i = sink; i ^ source; i = p[i]) flow = std::min(flow, c[p[i]][i] - f[p[i]][i]);
		for (int i = sink; i ^ source; i = p[i]) {
			mc += flow * d[p[i]][i];
			f[p[i]][i] += flow;
			f[i][p[i]] -= flow;
		}
		mf += flow;
	}

	return { mc, mf };
}

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> map[i];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			int idx = i * M + j + 1;
			a[sink].push_back(idx);
			a[idx].push_back(sink);
			c[idx][sink] = 1;

			if ((i ^ j) & 1) {
				a[source].push_back(idx);
				a[idx].push_back(source);
				c[source][idx] = 1;

				for (int k = 0; k < 4; ++k) {
					int di = i + dx[k], dj = j + dy[k];
					int dn = M * dx[k] + dy[k];

					if (di < 0 || di >= N || dj < 0 || dj >= M) continue;

					int cost = table[map[i][j] - 'A'][map[di][dj] - 'A'];

					a[idx].push_back(idx + dn);
					a[idx + dn].push_back(idx);
					c[idx][idx + dn] = 1;
					d[idx][idx + dn] = -cost;
					d[idx + dn][idx] = cost;
				}
			}
		}
	}

	auto result = MCMF(source, sink);

	std::cout << -result.first;
}