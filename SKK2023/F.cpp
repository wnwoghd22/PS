#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

typedef long long int ll;
const int LEN = 100'001;
std::vector<int> graph[LEN];
bool visited[LEN];
int N, u, v, A[LEN];

ll bfs() {
	ll result = A[1];
	std::queue<int> q;
	q.push(1);
	visited[1] = true;
	while (q.size()) {
		int u = q.front(); q.pop();
		for (const int v : graph[u]) {
			if (visited[v]) continue;
			if (A[v] > A[u])
				result += A[v] - A[u];
			visited[v] = true;
			q.push(v);
		}
	}
	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	for (int i = 1; i < N; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	std::cout << bfs();
}