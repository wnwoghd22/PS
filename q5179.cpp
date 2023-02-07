#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

typedef std::pair<int, int> pii;
const int INF = 1e9;
const int LEN = 501;
int P[LEN][LEN];
std::vector<int> graph[LEN];
std::vector<int> inv[LEN];
bool visited[LEN];
int N, M, s, d, u, v, p, dist[LEN];

void dijkstra(const int s) {
	for (int i = 0; i < N; ++i) dist[i] = INF;
	std::priority_queue<pii> q;
	dist[s] = 0;
	q.push({ 0, s });
	while (q.size()) {
		auto [d, u] = q.top(); q.pop();
		if (dist[u] < -d) continue;
		for (const int& v : graph[u]) {
			if (~P[u][v] && -d + P[u][v] < dist[v]) {
				dist[v] = -d + P[u][v];
				q.push({ -dist[v], v });
			}
		}
	}
}

void remove(const int d) {
	memset(visited, 0, sizeof visited);
	std::queue<int> q;
	q.push(d);
	visited[d] = true;
	while (q.size()) {
		int v = q.front(); q.pop();
		for (const int& u : inv[v]) {
			if (dist[u] + P[u][v] == dist[v]) {
				// std::cout << "remove:" << u << "->" << v << '\n';
				P[u][v] = -1;
				if (!visited[u]) {
					visited[u] = true;
					q.push(u);
				}
			}
		}
	}
}

bool solve() {
	std::cin >> N >> M;
	if (!N && !M) return false;
	memset(P, -1, sizeof P);
	for (std::vector<int>& v : graph) v.clear();
	for (std::vector<int>& v : inv) v.clear();
	std::cin >> s >> d;
	while (M--) {
		std::cin >> u >> v >> p;
		P[u][v] = p;
		graph[u].push_back(v);
		inv[v].push_back(u);
	}
	dijkstra(s);
	remove(d);
	dijkstra(s);
	std::cout << (dist[d] == INF ? -1 : dist[d]) << '\n';
	return true;
}

int main() {
	freopen("input.txt", "r", stdin);
	while (solve());
}