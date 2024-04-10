#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<int, int> pii;
const int LEN = 10'001;
int dist[LEN];
int incoming[LEN];
bool visited[LEN];
int distance[LEN][LEN];
std::vector<int> graph[LEN];
std::vector<int> inv[LEN];
int N, M, S, E, U, V, D;

int topological_sort(const int from, const int target) {
	std::queue<int> q;
	q.push(from);
	while (q.size()) {
		int u = q.front(); q.pop();
		if (u == target) break;
		for (const int& v : graph[u]) {
			int d = distance[u][v];
			if (!--incoming[v]) q.push(v);
			if (dist[u] + d > dist[v])
				dist[v] = dist[u] + d;
		}
	}
	return dist[target];
}
int back_track(const int target) {
	std::queue<int> q;
	q.push(target);
	visited[target] = true;
	int result = 0;
	while (q.size()) {
		int v = q.front(); q.pop();
		for (const int& u : inv[v]) {
			int d = distance[u][v];
			if (dist[u] + d == dist[v]) {
				++result;
				if (!visited[u]) {
					visited[u] = true;
					q.push(u);
				}
			}
		}
	}
	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	while (M--) {
		std::cin >> U >> V >> D;
		graph[U].push_back(V);
		inv[V].push_back(U);
		incoming[V]++;
		distance[U][V] = D;
	}
	std::cin >> S >> E;
	int max_dist = topological_sort(S, E);
	int count = back_track(E);
	std::cout << max_dist << '\n' << count;
}