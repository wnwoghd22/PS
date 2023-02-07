#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<int, int> pii;
const int LEN = 10'001;
int dist[LEN], cnt[LEN];
int incoming[LEN], flag[LEN];
std::vector<pii> graph[LEN];
int N, M, S, E, U, V, D;

pii topological_sort(const int target) {
	std::queue<int> q;
	for (int i = 0; i <= N; ++i)
		if (!incoming[i]) q.push(i);
	while (q.size()) {
		int u = q.front(); q.pop();
		if (u == target) break;
		for (const pii& e : graph[u]) {
			int v = e.first, d = e.second;
			if (!--incoming[v]) q.push(v);
			if (flag[u]) {
				flag[v] = true;
				if (dist[u] + d > dist[v]) {
					dist[v] = dist[u] + d;
					cnt[v] = cnt[u] + 1;
				}
				else if (dist[u] + d == dist[v]) {
					dist[v] = dist[u] + d;
					cnt[v] += cnt[u] + 1;
				}
			}
		}
	}
	return { dist[target], cnt[target] };
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	while (M--) {
		std::cin >> U >> V >> D;
		graph[U].push_back({ V, D });
		incoming[V]++;
	}
	std::cin >> S >> E;
	flag[S] = true;
	pii result = topological_sort(E);
	std::cout << result.first << '\n' << result.second;
}